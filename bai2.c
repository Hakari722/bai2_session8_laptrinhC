#include <stdio.h>

struct Account {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    int final_fee;
};

int main() {
    int N, i;
    struct Account list[100];
    int total_revenue = 0;
    int downgraded_count = 0;

    do {
        printf("Nhap so luong tai khoan (1 <= N <= 100): ");
        if (scanf("%d", &N) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        if (N < 1 || N > 100) {
            printf("So luong khong hop le. Vui long nhap lai!\n");
        }
    } while (N < 1 || N > 100);


    for (i = 0; i < N; i++) {
        printf("\n--- Nhap thong tin tai khoan thud %d ---\n", i + 1);
        
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &list[i].user_id);

        printf("Ten tai khoan (username): ");
        scanf("%s", list[i].username);

        do {
            printf("Loai goi (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &list[i].plan_type);
            if (list[i].plan_type < 1 || list[i].plan_type > 3) {
                printf("Loi: Loai goi phai tu 1 den 3. Nhap lai!\n");
            }
        } while (list[i].plan_type < 1 || list[i].plan_type > 3);

        do {
            printf("So ngay no cuoc (days_overdue >= 0): ");
            scanf("%d", &list[i].days_overdue);
            if (list[i].days_overdue < 0) {
                printf("Loi: So ngay no cuoc khong duoc am. Nhap lai!\n");
            }
        } while (list[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi (active_devices >= 0): ");
            scanf("%d", &list[i].active_devices);
            if (list[i].active_devices < 0) {
                printf("Loi: So thiet bi khong duoc am. Nhap lai!\n");
            }
        } while (list[i].active_devices < 0);
    }

    for (i = 0; i < N; i++) {
        int base_fee = 0;

        if (list[i].days_overdue >= 3) {
            if (list[i].plan_type != 1) {
                list[i].plan_type = 1; 
                downgraded_count++;
            }
            list[i].final_fee = 0;
        } else {
    
            if (list[i].plan_type == 1) {
                base_fee = 0;
            } else if (list[i].plan_type == 2) {
                base_fee = 120000;
            } else if (list[i].plan_type == 3) {
                base_fee = 250000;
            }

            list[i].final_fee = base_fee;

            if (list[i].plan_type == 2 && list[i].active_devices > 1) {
                int extra_devices = list[i].active_devices - 1;
                int penalty = extra_devices * 30000;
                list[i].final_fee += penalty;
            }
        }

        total_revenue += list[i].final_fee;
    }

    printf("\n=================================================================================\n");
    printf("                       BAO CAO DOI SOAT & XU LY NO CUOC                         \n");
    printf("=================================================================================\n");
    printf("%-10s %-20s %-10s %-12s %-12s %-15s\n", 
           "MA TK", "TEN TK", "GOI CUOC", "THIET BI", "NO (NGAY)", "PHI THUC THU");
    printf("---------------------------------------------------------------------------------\n");

    for (i = 0; i < N; i++) {
        printf("%-10d %-20s %-10d %-12d %-12d %-15d\n",
               list[i].user_id,
               list[i].username,
               list[i].plan_type,
               list[i].active_devices,
               list[i].days_overdue,
               list[i].final_fee);
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc te thu duoc trong ky : %d VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap ve goi Free  : %d tai khoan\n", downgraded_count);
    printf("=================================================================================\n");

    return 0;
}