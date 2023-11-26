#include <iostream>
#include <cmath>
#include <fstream>

# define PI           3.14159265358979323846 

using namespace std;

    // ����� �������� (����� ����������� �����)
#include <cmath>

double fixed_point_iteration(double M, double e, double epsilon = 1e-6)
{
    double E = M;
    double E_next;

    for (int i = 0; i <= 30; i++)  //���� ��� ������ ���-�� �������� � �������� �������
    {
        E_next = e * sin(E) + M;   // ��������� �������� E
        if (fabs(E_next - E) < epsilon)
            return E_next;

        E = E_next;                // ��������� ����� �������� E_next
    }

    return 0;
}

double bisection_method(double M, double e, double epsilon = 1e-6)
{
    double x = M - 5; // ����� ������������� ��������
    double y = M + 5;  // ����� ������������� ��������
    double z = 0;

    for (int i = 0; i <= 100; i++)
    {
        z = (x + y) / 2; // ��������� ����� �������� �������
        if (fabs(y - x) < (2 * epsilon))
            return z;

        if (((x - e * sin(x) - M) * (y - e * sin(y) - M)) < 0)
        {
            y = z; // ��������� ������ ������� �������
        }
        else
        {
            x = z; // ��������� ����� ������� �������
        }
    }

    return z;
}

double golden_section_method(double M, double e, double epsilon = 1e-6)
{
    double x = M - 5; // ����� ������������� ��������
    double y = M + 5; // ����� ������������� ��������
    double z = 0;
    double phi = (sqrt(5) + 1) / 2; // ������� �������

    for (int i = 0; i <= 30; i++)
    {
        z = x + (y - x) / phi; // ��������� ����� �������� �������
        if (fabs(y - x) < 2 * epsilon)
            return z;

        if ((x - e * sin(x) - M) * (y - e * sin(y) - M) < 0)
        {
            y = z; // ��������� ������ ������� �������
        }
        else
        {
            x = z; // ��������� ����� ������� �������
        }
    }

    return z;
}

double newton_method(double M, double e, double epsilon = 1e-6)
{
    double E = M; // ��������� ����������� ��� E

    for (int i = 0; i < 40; i++)
    {
        double f = E - e * sin(E) - M; // �������� �������
        double f_prime = 1 + e * cos(E); // �������� ����������� �������

        E -= f / f_prime; // ���������� ���������� ����������� ��� E

        if (abs(f) < epsilon) // �������� ������� ����������
        {
            break;
        }
    }

    return abs(E);
}

int main() {
    // ��������� ������
    double T = 9015;                        // ������ ��������� �� � ��������
    double r_a = 1017000;                   // � ������ ���������
    double r_p = 350000;                    // � ������ ���������� 
    double epsilon = 1e-6;

    double n = 2 * PI / T;                  // ������� ������� �������� 
    double a = (r_a + r_p) / 2;             // ������� ������� 
    double e = ((r_a - r_p) / (2 * a));     // ������������� ������ 0,48793

    // �������� �����
    ofstream fout1;
    fout1.open("File1.txt");

    // �������� ��������� �������� �����
    if (!fout1) {
        cout << "Error opening file.";
        return 0;
    }

    fout1 << "t, c\t";
    fout1 << "M(t), ���\t";
    fout1 << "E(t), ���\t";
    fout1 << "Theta(t), ���\t" << endl;

    // ���������� � ������ �������� �������� � ����
    for (int t = 0; t <= T; t++) {
        fout1 << t << "\t";

        double M = n * t; // ������� ��������
        double E = newton_method(M, e, epsilon); // ��������������� ��������
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // �������� ��������

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout1 << M << "\t";
        fout1 << E << "\t";
        fout1 << true_anomaly << endl;
    }

    fout1.close();
    cout << "The data was successfully written to the 'File1.txt'.";

    ofstream fout2;
    fout2.open("File2.txt");

    // �������� ��������� �������� �����
    if (!fout2) {
        cout << "Error opening file.";
        return 0;
    }

    fout2 << "t, c\t";
    fout2 << "M(t), ���\t";
    fout2 << "E(t), ���\t";
    fout2 << "Theta(t), ���\t" << endl;

    // ���������� � ������ �������� �������� � ����
    for (int t = 0; t <= T; t++) {
        fout2 << t << "\t";

        double M = n * t; // ������� ��������
        double E = golden_section_method(M, e, epsilon); // ��������������� ��������
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // �������� ��������

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout2 << M << "\t";
        fout2 << E << "\t";
        fout2 << true_anomaly << endl;
    }

    fout2.close();
    cout << "The data was successfully written to the 'File2.txt'.";

    // �������� �����
    ofstream fout3;
    fout3.open("File3.txt");

    // �������� ��������� �������� �����
    if (!fout3) {
        cout << "Error opening file.";
        return 0;
    }

    fout3 << "t, c\t";
    fout3 << "M(t), ���\t";
    fout3 << "E(t), ���\t";
    fout3 << "Theta(t), ���\t" << endl;

    // ���������� � ������ �������� �������� � ����
    for (int t = 0; t <= T; t++) {
        fout3 << t << "\t";

        double M = n * t; // ������� ��������
        double E = bisection_method(M, e, epsilon); // ��������������� ��������
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // �������� ��������

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout3 << M << "\t";
        fout3 << E << "\t";
        fout3 << true_anomaly << endl;
    }

    fout3.close();
    cout << "The data was successfully written to the 'File3.txt'.";

    // �������� �����
    ofstream fout4;
    fout4.open("File4.txt");

    // �������� ��������� �������� �����
    if (!fout4) {
        cout << "Error opening file.";
        return 0;
    }

    fout4 << "t, c\t";
    fout4 << "M(t), ���\t";
    fout4 << "E(t), ���\t";
    fout4 << "Theta(t), ���\t" << endl;

    // ���������� � ������ �������� �������� � ����
    for (int t = 0; t <= T; t++) {
        fout4 << t << "\t";

        double M = n * t; // ������� ��������
        double E = fixed_point_iteration(M, e, epsilon); // ��������������� ��������
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // �������� ��������

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout4 << M << "\t";
        fout4 << E << "\t";
        fout4 << true_anomaly << endl;
    }

    fout4.close();
    cout << "The data was successfully written to the 'File4.txt'.";

    return 0;
}