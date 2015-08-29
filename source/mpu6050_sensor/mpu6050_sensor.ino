#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050 sensor;

double t = 0;
long position_x = 0;
double Roll = 0;
long r_x_offset = 0;   // X 陀螺仪偏移， 通过取平均值计算出来
long a_z_offset = 0;
long a_y_offset = 0;
long total = 0;
long sample_times = 100; // 取样次数， 求差值

////////////////////////

/* 通过卡尔曼滤波得到的最终角度 */
float Angle = 0.0;
/*由角速度计算的倾斜角度 */
float Angle_gy = 0.0;
float Q_angle = 0.9;
float Q_gyro = 0.001;
float R_angle = 0.5;
float dt = 0.01;
/* dt为kalman滤波器采样时间; */
char  C_0 = 1;
float Q_bias, Angle_err;
float PCt_0 = 0.0, PCt_1 = 0.0, E = 0.0;
float K_0 = 0.0, K_1 = 0.0, t_0 = 0.0, t_1 = 0.0;
float Pdot[4] = { 0, 0, 0, 0 };
float PP[2][2] = { { 1, 0 }, { 0, 1 } };
/* 卡尔曼滤波函数,具体实现可以参考网上资料,也可以使用其它滤波算法 */
void Kalman_Filter(float Accel, float Gyro)
{
    Angle += (Gyro - Q_bias) * dt;
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0];
    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;
    PP[0][1] += Pdot[1] * dt;
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;
    Angle_err = Accel - Angle;
    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];
    E = R_angle + C_0 * PCt_0;
    if (E != 0) {
        K_0 = PCt_0 / E;
        K_1 = PCt_1 / E;
    }
    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];
    PP[0][0] -= K_0 * t_0;
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;
    Angle += K_0 * Angle_err;
    Q_bias += K_1 * Angle_err;
}
///////////////

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    sensor.initialize();

    long acc[3] = { 0 };
    long rot[3] = { 0 };
    for (int i = 0; i < 20; i++) {
        int ax, ay, az;
        int gx, gy, gz;

        sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        acc[0] += ax;
        acc[1] += ay;
        acc[2] += az;

        rot[0] += gx;
        rot[1] += gy;
        rot[2] += gz;

        delay(100);
    }

    r_x_offset = rot[0] / 20;

    a_y_offset = acc[1] / 20;
    a_z_offset = acc[2] / 20;
    t = millis();
}

// the loop function runs over and over again until power down or reset
void loop()
{
    int ax, ay, az;
    int gx, gy, gz;

    double delta_time = (double)(millis() - t) / 1000.0f;
    t = millis();

    sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    double tax = (double)ax / 16384.0f;
    double tay = (double)ay / 16384.0f;
    double taz = (double)az / 16384.0f;

    double Angle_accX = atan2(tay, taz) * 180 / 3.14159;

    double angle_acc = atan2(ay - a_y_offset, az - a_z_offset) * 180.0f / 3.14f;
    double angle_speed = (gx - r_x_offset) / 131.0f;

    Roll += angle_speed * delta_time;

    Kalman_Filter(Angle_accX, Roll);

    Serial.print(angle_speed);
    Serial.print(","); Serial.print(Roll);
    Serial.print(","); Serial.print(Angle_accX);
    Serial.print(","); Serial.print(Angle);
    //// Serial.print(","); Serial.print(a_z_offset);
    Serial.println();

    delay(10);
}

