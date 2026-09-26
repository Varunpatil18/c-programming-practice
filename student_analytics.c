 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILE_NAME "students_data.csv"

typedef struct {
    int roll_no;
    char name[MAX_NAME_LEN];
    int total_credits;
    float cgpa;
} Student;

typedef struct {
    Student *data;
    size_t count;
    size_t capacity;
} Database;

void init_db(Database *db) {
    db->capacity = 4;
    db->count = 0;
    db->data = (Student *)malloc(db->capacity * sizeof(Student));
    if (!db->data) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void free_db(Database *db) {
    free(db->data);
    db->data = NULL;
    db->count = 0;
    db->capacity = 0;
}

void ensure_capacity(Database *db) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        Student *temp = (Student *)realloc(db->data, db->capacity * sizeof(Student));
        if (!temp) {
            printf("Memory reallocation failed!\n");
            free_db(db);
            exit(1);
        }
        db->data = temp;
    }
}

int compare_by_roll(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return (s1->roll_no - s2->roll_no);
}

int compare_by_cgpa_desc(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s2->cgpa > s1->cgpa) return 1;
    if (s2->cgpa < s1->cgpa) return -1;
    return 0;
}

int binary_search_roll(const Database *db, int target_roll) {
    int low = 0;
    int high = (int)db->count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (db->data[mid].roll_no == target_roll) {
            return mid;
        } else if (db->data[mid].roll_no < target_roll) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void load_from_file(Database *db) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return;

    Student s;
    while (fscanf(fp, "%d,%49[^,],%d,%f\n", &s.roll_no, s.name, &s.total_credits, &s.cgpa) == 4) {
        ensure_capacity(db);
        db->data[db->count++] = s;
    }
    fclose(fp);
    qsort(db->data, db->count, sizeof(Student), compare_by_roll);
}

void save_to_file(const Database *db) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("Error: Could not save data to file.\n");
        return;
    }

    for (size_t i = 0; i < db->count; i++) {
        fprintf(fp, "%d,%s,%d,%.2f\n",
                db->data[i].roll_no,
                db->data[i].name,
                db->data[i].total_credits,
                db->data[i].cgpa);
    }
    fclose(fp);
}

void add_student(Database *db) {
    Student s;
    printf("\nEnter Roll Number: ");
    if (scanf("%d", &s.roll_no) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    qsort(db->data, db->count, sizeof(Student), compare_by_roll);
    if (binary_search_roll(db, s.roll_no) != -1) {
        printf("Error: Student with Roll Number %d already exists.\n", s.roll_no);
        return;
    }

    printf("Enter Name (no spaces or commas): ");
    scanf("%49s", s.name);

    printf("Enter Completed Credits: ");
    scanf("%d", &s.total_credits);

    printf("Enter CGPA (0.00 - 10.00): ");
    scanf("%f", &s.cgpa);

    if (s.cgpa < 0.0f || s.cgpa > 10.0f) {
        printf("Invalid CGPA entered. Record rejected.\n");
        return;
    }

    ensure_capacity(db);
    db->data[db->count++] = s;
    qsort(db->data, db->count, sizeof(Student), compare_by_roll);
    save_to_file(db);

    printf("Record registered successfully.\n");
}

void search_student(const Database *db) {
    if (db->count == 0) {
        printf("\nDatabase is currently empty.\n");
        return;
    }

    int roll;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);
 int idx = binary_search_roll(db, roll);
    if (idx != -1) {
        printf("\nStudent Found:\n");
        printf("--------------------------------------------------\n");
        printf("Roll No: %d\n", db->data[idx].roll_no);
        printf("Name:    %s\n", db->data[idx].name);
        printf("Credits: %d\n", db->data[idx].total_credits);
        printf("CGPA:    %.2f\n", db->data[idx].cgpa);
        printf("--------------------------------------------------\n");
    } else {
        printf("No student found with Roll Number %d.\n", roll);
    }
}

void display_leaderboard(const Database *db) {
    if (db->count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    Student *copy = (Student *)malloc(db->count * sizeof(Student));
    if (!copy) {
        printf("Memory allocation failed for ranking.\n");
        return;
    }
    memcpy(copy, db->data, db->count * sizeof(Student));
    qsort(copy, db->count, sizeof(Student), compare_by_cgpa_desc);

    printf("\n================ Academic Leaderboard ================\n");
    printf("%-6s | %-10s | %-20s | %-8s | %-6s\n", "Rank", "Roll No", "Name", "Credits", "CGPA");
    printf("------------------------------------------------------\n");

    for (size_t i = 0; i < db->count; i++) {
        printf("%-6zu | %-10d | %-20s | %-8d | %-6.2f\n",
               i + 1,
               copy[i].roll_no,
               copy[i].name,
               copy[i].total_credits,
               copy[i].cgpa);
    }
    printf("======================================================\n");
    free(copy);
}

void display_analytics(const Database *db) {
    if (db->count == 0) {
        printf("\nNo records to compute statistics.\n");
        return;
    }

    float sum_cgpa = 0.0f;
    float max_cgpa = db->data[0].cgpa;
    float min_cgpa = db->data[0].cgpa;
    int dist_count = 0; // CGPA >= 8.5

    for (size_t i = 0; i < db->count; i++) {
        float val = db->data[i].cgpa;
        sum_cgpa += val;
        if (val > max_cgpa) max_cgpa = val;
        if (val < min_cgpa) min_cgpa = val;
        if (val >= 8.5f) dist_count++;
    }

    printf("\n================ Cohort Analytics ================\n");
    printf("Total Enrolled Students: %zu\n", db->count);
    printf("Class Average CGPA:      %.2f\n", sum_cgpa / db->count);
    printf("Highest CGPA:            %.2f\n", max_cgpa);
    printf("Lowest CGPA:             %.2f\n", min_cgpa);
    printf("Dean's Honors (>= 8.50): %d (%.1f%%)\n", dist_count, (dist_count * 100.0f) / db->count);
    printf("==================================================\n");
}

int main(void) {
    Database db;
    init_db(&db);
    load_from_file(&db);

    int choice = 0;
    while (choice != 5) {
        printf("\n--- Student Analytics & Ranking Engine ---\n");
        printf("1. Add New Student Record\n");
        printf("2. Search Student by Roll Number (Binary Search)\n");
        printf("3. View Rank Leaderboard (Sorted by CGPA)\n");
        printf("4. View Cohort Analytics\n");
        printf("5. Exit\n");
        printf("Enter Choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection. Try again.\n");
            continue;
        }

        switch (choice) {
            case 1: add_student(&db); break;
            case 2: search_student(&db); break;
            case 3: display_leaderboard(&db); break;
            case 4: display_analytics(&db); break;
            case 5: printf("Exiting engine. Memory freed.\n"); break;
            default: printf("Option not recognized.\n"); break;
        }
    }

    free_db(&db);
    return 0;
}