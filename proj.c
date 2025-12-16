#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void showIntro(void)
{
    system("clear");
    printf("\033[1;36m");
    printf("================================================================================\n");
    printf("                   CAR ASSISTANT SYSTEM(FUEL TRACKER+FAULT DIAGNOSIS)                        \n");
    printf("================================================================================\n\033[0m");
    printf("   \033[1mProject Title   \033[0m: Car Assistant System(Fuel Tracker+Fault Diagnosis\n");
    printf("   \033[1mSubmitted By    \033[0m: Pratik Agarwal\n");
    printf("   \033[1mSAP ID          \033[0m: 590023543\n");
    printf("   \033[1mBatch           \033[0m: B09\n");
    printf("   \033[1mCollege         \033[0m: UPES, School of Computer Science\n");
    printf("   \033[1mSubmitted To    \033[0m: Professor Pankaj Badoni\n\n");
    printf("\033[1;33m");
    printf("================================================================================\n");
    printf("                        Press Enter to continue...                              \n");
    printf("================================================================================\n");
    printf("\033[0m");
    getchar();
}
struct trip
{//it helps us group all the trip values
    char date[30];
    float distance;
    float fuel;
    int speed;
    float mileage;
    float ecoscore;
};
struct fault
{ // Fault database
    char check[200];
    char symptom[100];
    float severity;
};
// structure to store the profile
struct prof
{
    char name[40];
    char car[40];
    char fuel[16];
    char lastservice[20];
};
// For storing trips
struct trip listtrip[500]; // for storing the trips
int tripcounting = 0;      // number of total trips stored
struct prof profile;       // profile of the user
void checkfile(const char *filename)
{//helps us ensure if a file exists by opening it in append mode
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error in creating the file:%s\n", filename);
        exit(1);
    }
    fclose(fp);
}
// taking the integer value input
int inputi()
{
    int x;
    while (scanf("%d", &x) != 1)
    {
        printf("The input is invalid. Please enter an integer value: ");
        while (getchar() != '\n')
            ;
    }
    return x;
}
// taking the float value input
float inputf()
{
    float x;
    while (scanf("%f", &x) != 1)
    {
        printf("The inpiut is invalid. Please enter a float value: ");
        while (getchar() != '\n')
            ;
    }
    return x;
}
void loadtrip();
void savetrip();
void addtrip();
void viewtrip();
void searchDate();
void edittrip();
void deletetrip();
void sorttripmenu();
void analyticsmenu();
void faultdiagnose();
void loadprofile();
void saveprofile();
void editprofile();
void showprofile();
void deleteprofile();
float mileage(float distance, float fuel)
{//checks the boundary conditions too
    if (fuel <= 0)
    {
        printf("No fuel was added or invalid input");
        return 0.0f;
    }
    return distance / fuel;
}
float ecoscore(float speed)
{
    if (speed >= 40 && speed <= 80)
    {
        printf("You are driving in the ideal speed range!!");
        return 90.00f;
    }
    else if (speed > 80)
    {
        printf("You are driving too fast, less eco friendly");
        return 60.00f;
    }
    else
    {
        printf("You are driving in the mid speed range, medium eco friendly");
        return 70.00f;
    }
}
void loadtrip()
{// reads the saved trip records
    FILE *fp;
    checkfile("fuel_data.txt");
    fp = fopen("fuel_data.txt", "r");
    if (fp == NULL)
    {
        printf("An Error occured in reading the file.\n");
        return;
    }
    tripcounting = 0;
    while (tripcounting < 500 &&
           fscanf(fp, "%29s %f %f %d %f %f",
                  listtrip[tripcounting].date,
                  &listtrip[tripcounting].distance,
                  &listtrip[tripcounting].fuel,
                  &listtrip[tripcounting].speed,
                  &listtrip[tripcounting].mileage,
                  &listtrip[tripcounting].ecoscore) == 6)
    {
        tripcounting++;
    }
    fclose(fp);
}
void savetrip()
{
    FILE *fp = fopen("fuel_data.txt", "w");
    int i;
    if (fp == NULL)
    {
        printf("An error occured while writing the file.\n");
        return;
    }
    for (i = 0; i < tripcounting; i++)
    {
        fprintf(fp, "%s %.2f %.2f %d %.2f %.2f\n",
                listtrip[i].date,
                listtrip[i].distance,
                listtrip[i].fuel,
                listtrip[i].speed,
                listtrip[i].mileage,
                listtrip[i].ecoscore);
    }
    fclose(fp);
}
void addtrip()
{
    if (tripcounting >= 500)
    {
        printf("\nThe limit for the trips has been reached. Delete trips to add more trips.\n");
        return;
    }
    struct trip t;
    printf("Enter the Date(DD/MM/YYYY): ");
    scanf("%29s", t.date);
    while (getchar() != '\n');
    printf("Enter the Distance(km): ");
    t.distance = inputf();
    printf("Enter the Fuel used during the Trip (in Litres): ");
    t.fuel = inputf();
    printf("Enter the Average Speed during the Trip (km/h): ");
    t.speed = inputi();
    t.mileage = mileage(t.distance, t.fuel);
    t.ecoscore = ecoscore(t.speed);
    printf("\nThe calculated Mileage is %.2f km/L.\n", t.mileage);
    printf("Eco Score: %.2f\n", t.ecoscore);
    listtrip[tripcounting] = t;
    tripcounting++;
    savetrip();
    printf("\nTrip added & saved successfully.\n");
}

void viewtrip()
{
    int i;
    if (tripcounting == 0)
    {
        printf("\nNo trips are available to display.\n");
        return;
    }
    for (i = 0; i < tripcounting; i++)
    {
        printf("%d Date: %s | Distance: %.2f km | Fuel: %.2f L | Speed: %d km/h | Mileage: %.2f km/L | Eco: %.2f\n",
               i + 1,
               listtrip[i].date,
               listtrip[i].distance,
               listtrip[i].fuel,
               listtrip[i].speed,
               listtrip[i].mileage,
               listtrip[i].ecoscore);
    }
}
void searchDate()
{
    char searchdate[30];
    int i, found = 0;
    if (tripcounting == 0)
    {
        printf("\n No Trips to search.\n");
        return;
    }
    printf("\n Enter date to search (DD/MM/YYYY): ");
    scanf("%29s", searchdate);
    printf("\n Trips on %s:\n", searchdate);
    for (i = 0; i < tripcounting; i++)
    {
        if (strcmp(listtrip[i].date, searchdate) == 0)
        {
            printf("%d Date: %s | Distance: %.2f km | Fuel: %.2f L | Speed: %.2f km/h | Mileage: %.2f km/L | Eco Score: %.2f\n",
                   i + 1,
                   listtrip[i].date,
                   listtrip[i].distance,
                   listtrip[i].fuel,
                   listtrip[i].speed,
                   listtrip[i].mileage,
                   listtrip[i].ecoscore);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No trips were found for the date entered.\n");
    }
}
void edittrip()
{
    int index;
    if (tripcounting == 0)
    {
        printf("\nNo trips are available to edit.\n");
        return;
    }
    printf("\n Existing Trips:\n");
    viewtrip();
    printf("\n ENter index of the trip you want to edit: ");
    index = inputi();
    if (index < 1 || index > tripcounting)
    {
        printf("Invalid Index.\n");
        return;
    }
    index--;
    printf("\n Editimng Trip #%d\n", index + 1);
    printf("Current Date: %s\n", listtrip[index].date);
    printf("ENter new Date(DD/MM/YYYY): ");
    scanf("%29s", listtrip[index].date);
    printf("Current Distance: %.2f km\n", listtrip[index].distance);
    printf("ENte rthe new Distance(in km): ");
    listtrip[index].distance = inputf();
    printf("Current Fuel Entered: %.2f L\n", listtrip[index].fuel);
    printf("Enter new fuel (in Litres): ");
    listtrip[index].fuel = inputf();
    printf("Current Speed entered: %d km/h\n", listtrip[index].speed);
    printf("Enter the new speed (km/h): ");
    listtrip[index].speed = inputf();
    listtrip[index].mileage = mileage(listtrip[index].distance, listtrip[index].fuel);
    listtrip[index].ecoscore = ecoscore(listtrip[index].speed);
    printf("\n Updated trip detailss are:\n");
    printf("%d Date: %s | Distance: %.2f km | Fuel: %.2f L | Speed: %d km/h | Mileage: %.2f km/L | Eco Score: %.2f\n",
           index + 1,
           listtrip[index].date,
           listtrip[index].distance,
           listtrip[index].fuel,
           listtrip[index].speed,
           listtrip[index].mileage,
           listtrip[index].ecoscore);
    savetrip();
    printf("\n Trip Updated Successfully");
}
void deletetrip()
{
    int index, i;
    if (tripcounting == 0)
    {
        printf("\nNo trips to delete.\n");
        return;
    }
    printf("\n Existing trips:\n");
    viewtrip();
    printf("\n Enter index of trip to delete: ");
    index = inputi();
    if (index < 1 || index > tripcounting)
    {
        printf("Invalid index.\n");
        return;
    }
    index--;
    printf("\nDeleting Trip # %d: Date: %s | Distance: %.2f km | Fuel: %.2f L | Speed: %d km/h\n",
           index + 1,
           listtrip[index].date,
           listtrip[index].distance,
           listtrip[index].fuel,
           listtrip[index].speed);
    for (i = index; i < tripcounting - 1; i++)
    {
        listtrip[i] = listtrip[i + 1];
    }
    tripcounting--;
    savetrip();
    printf("\n Trip deleted successfully.\n");
}
void swaptrip(struct trip *a, struct trip *b)
{
    struct trip temp = *a;
    *a = *b;
    *b = temp;
}
void sorttripmenu()
{
    int choice, order;
    int i, j;
    if (tripcounting <= 1)
    {
        printf("\n There are not enough trips to sort.\n");
        return;
    }
    printf("1. By Distance\n");
    printf("2. By Fuel\n");
    printf("3. By Speed\n");
    printf("4. By Mileage\n");
    printf("5. By Date \n");
    printf("Enter choice: ");
    choice = inputi();
    printf("Order: 1.Ascending 2.Descending: ");
    order = inputi();
    for (i = 0; i < tripcounting - 1; i++)
    {
        for (j = 0; j < tripcounting - i - 1; j++)
        {
            int swap = 0;
            if (choice == 1)
            {
                if (order == 1 && listtrip[j].distance > listtrip[j + 1].distance)
                {
                    swap = 1;
                }
                if (order == 2 && listtrip[j].distance < listtrip[j + 1].distance)
                {
                    swap = 1;
                }
            }
            else if (choice == 2)
            {
                if (order == 1 && listtrip[j].fuel > listtrip[j + 1].fuel)
                    swap = 1;
                if (order == 2 && listtrip[j].fuel < listtrip[j + 1].fuel)
                    swap = 1;
            }
            else if (choice == 3)
            {
                if (order == 1 && listtrip[j].speed > listtrip[j + 1].speed)
                    swap = 1;
                if (order == 2 && listtrip[j].speed < listtrip[j + 1].speed)
                    swap = 1;
            }
            else if (choice == 4)
            {
                if (order == 1 && listtrip[j].mileage > listtrip[j + 1].mileage)
                    swap = 1;
                if (order == 2 && listtrip[j].mileage < listtrip[j + 1].mileage)
                    swap = 1;
            }
            else if (choice == 5)
            {
                int cmp = strcmp(listtrip[j].date, listtrip[j + 1].date);
                if (order == 1 && cmp > 0)
                    swap = 1;
                if (order == 2 && cmp < 0)
                    swap = 1;
            }
            if (swap)
            {
                swaptrip(&listtrip[j], &listtrip[j + 1]);
            }
        }
    }
    savetrip();
    printf("\nTrips sorted Successfully.\n");
    viewtrip();
}
void loadprofile()
{
    FILE *fp;
    checkfile("profilee.txt");
    fp = fopen("profilee.txt", "r");
    if (fp == NULL)
    {
        strcpy(profile.name, "None");
        strcpy(profile.car, "None");
        strcpy(profile.fuel, "None");
        strcpy(profile.lastservice, "None");
        return;
    }
    if (fscanf(fp, "%39s %39s %15s %19s",profile.name,profile.car,profile.fuel,profile.lastservice) != 4)
    {
        strcpy(profile.name, "None");
        strcpy(profile.car, "None");
        strcpy(profile.fuel, "None");
        strcpy(profile.lastservice, "None");
    }
    fclose(fp);
}
void saveprofile()
{
    FILE *fp = fopen("profilee.txt", "w");
    if (fp == NULL)
    {
        printf("An error occured while saving the profile.\n");
        return;
    }
    fprintf(fp, "%s %s %s %s\n",
            profile.name,
            profile.car,
            profile.fuel,
            profile.lastservice);
    fclose(fp);
}

void editprofile()
{
    char temp[80];
    printf("\nCurrent Profile:\n");
    showprofile();
    printf("\nEnter name: ");
    scanf("%39s", profile.name);
    while (getchar() != '\n');
    printf("Enter car model/name: ");
    scanf("%39s", profile.car);
    while (getchar() != '\n');
    printf("Enter fuel type (Petrol/Diesel/CNG/Electric): ");
    scanf("%15s", profile.fuel);
    while (getchar() != '\n');
    printf("Enter last service date (DD/MM/YYYY): ");
    scanf("%19s", profile.lastservice);
    while (getchar() != '\n');
    saveprofile();
    printf("\nProfile updated and saved.\n");
}
void showprofile()
{
    printf("\nProfile:\n");
    printf("Name        : %s\n", profile.name);
    printf("Car         : %s\n", profile.car);
    printf("Fuel Type   : %s\n", profile.fuel);
    printf("Last Service: %s\n", profile.lastservice);
}
void deleteprofile()
{
    FILE *fp = fopen("profilee.txt", "w");
    if (fp == NULL)
    {
        printf("\nAn error occured while deleting the profile.\n");
        return;
    }
    fclose(fp);
    strcpy(profile.name, "None");
    strcpy(profile.car, "None");
    strcpy(profile.fuel, "None");
    strcpy(profile.lastservice, "None");
    printf("\nProfile deleted successfully.\n");
}
void analyticsmenu()
{
    if (tripcounting == 0)
    {
        printf("\nNo trips available for analytics.\n");
        return;
    }
    int i;
    float totalDistance = 0.0f, totalFuel = 0.0f, totalMileage = 0.0f;
    float bestMileage = -1.0f, worstMileage = -1.0f;
    float bestEco = -1.0f, worstEco = -1.0f;
    int bestEcoIndex = -1, worstEcoIndex = -1;

    for (i = 0; i < tripcounting; i++)
    {
        totalDistance += listtrip[i].distance;
        totalFuel += listtrip[i].fuel;
        totalMileage += listtrip[i].mileage;
        if (bestMileage < 0 || listtrip[i].mileage > bestMileage)
            bestMileage = listtrip[i].mileage;
        if (worstMileage < 0 || listtrip[i].mileage < worstMileage)
            worstMileage = listtrip[i].mileage;
        if (bestEco < 0 || listtrip[i].ecoscore > bestEco)
        {
            bestEco = listtrip[i].ecoscore;
            bestEcoIndex = i;
        }
        if (worstEco < 0 || listtrip[i].ecoscore < worstEco)
        {
            worstEco = listtrip[i].ecoscore;
            worstEcoIndex = i;
        }
    }
    printf("\n--- Analytics ---\n");
    printf("Total trips recorded : %d\n", tripcounting);
    printf("Total distance covered: %.2f km\n", totalDistance);
    printf("Total fuel consumed   : %.2f L\n", totalFuel);
    printf("Average mileage (mean of recorded mileages): %.2f km/L\n", totalMileage / tripcounting);
    printf("Best mileage recorded : %.2f km/L\n", bestMileage);
    printf("Worst mileage recorded: %.2f km/L\n", worstMileage);
    if (bestEcoIndex >= 0)
    {
        printf("Most eco-friendly trip: #%d Date:%s EcoScore:%.2f\n", bestEcoIndex + 1, listtrip[bestEcoIndex].date, listtrip[bestEcoIndex].ecoscore);
    }
    if (worstEcoIndex >= 0)
    {
        printf("Least eco-friendly trip: #%d Date:%s EcoScore:%.2f\n", worstEcoIndex + 1, listtrip[worstEcoIndex].date, listtrip[worstEcoIndex].ecoscore);
    }
}
void faultdiagnose()
{
    // Predefined small fault database
    struct fault faults[] = {
        {"Check engine light", "engine_light", 8.0f},
        {"Strange knocking noise from engine", "knocking", 7.5f},
        {"Car pulling to one side", "pulling", 5.0f},
        {"Brakes making noise", "brake_noise", 6.0f},
        {"Battery not holding charge", "battery", 7.0f},
        {"AC not cooling", "ac", 4.0f}};
    int faultCount = sizeof(faults) / sizeof(faults[0]);
    char input[200];
    printf("\nEnter symptom keywords (e.g. engine_light, knocking, pulling, brake_noise, battery, ac): ");
    scanf("%199s", input);
    while (getchar() != '\n');
    printf("\nPossible matches:\n");
    int found = 0;
    for (int i = 0; i < faultCount; i++)
    {
        if (strstr(faults[i].symptom, input) != NULL || strstr(faults[i].check, input) != NULL)
        {
            printf("- %s (Severity: %.1f/10)\n", faults[i].check, faults[i].severity);
            found = 1;
        }
    }
    if (!found)
    {
        for (int i = 0; i < faultCount; i++)
        {
            if (strstr(faults[i].check, input) != NULL || strstr(faults[i].symptom, input) != NULL)
            {
                printf("- %s (Severity: %.1f/10)\n", faults[i].check, faults[i].severity);
                found = 1;
            }
        }
    }
    if (!found)
    {
        printf("No matching faults found for your input. Try a different keyword (e.g. 'battery' or 'knocking').\n");
    }
    else
    {
        printf("\nNote: This is a basic rule-based suggestion system. For accurate diagnosis, consult a qualified mechanic.\n");
    }
}
void showThankYou(void)
{
    system("clear");
    printf("\n\n");
    printf("\033[1;36m");
    printf("================================================================================\n");
    printf("                                  THANK YOU                                      \n");
    printf("================================================================================\n");
    printf("\033[0m\n");
    // Message
    printf("   This project was developed as part of the Mini Project for the C programming Course.\n");
    printf("   \033[1m Car Assistant System(Fuel Tracker+Fault Diagnosis.\033[0m\n\n");

    printf("   Submitted By   : Pratik Agarwal\n");
    printf("   Batch          : B09\n");
    printf("   SAP ID         : 590023543\n");
    printf("   College        : UPES, School of Computer Science\n\n");
    // Footer
    printf("\033[1;33m");
    printf("================================================================================\n");
    printf("                     Press Enter to exit the program...                          \n");
    printf("================================================================================\n");
    printf("\033[0m");
    getchar();
}
int main(void)
{
    showIntro();
    int choice;
    loadtrip();
    loadprofile();
    if (strcmp(profile.name, "None") == 0)
    {
        printf("\nNo profile found. Please create your profile.\n");
        editprofile(); // <- asks name, car, fuel type, last service
    }
    loadprofile();
    while (1)
    {
        printf("1. Add trip\n");
        printf("2. View all trips\n");
        printf("3. Search trips by date\n");
        printf("4. Edit a trip\n");
        printf("5. Delete a trip\n");
        printf("6. Sort trips\n");
        printf("7. Profile: View/Edit/Delete\n");
        printf("8. Analytics (summary)\n");
        printf("9. Fault diagnosis (basic)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        choice = inputi();
        switch (choice)
        {
        case 1:
            addtrip();
            break;
        case 2:
            viewtrip();
            break;
        case 3:
            searchDate();
            break;
        case 4:
            edittrip();
            break;
        case 5:
            deletetrip();
            break;
        case 6:
            sorttripmenu();
            break;
        case 7:
        {
            int pchoice;
            while (1)
            {
                printf("\nProfile Menu:\n");
                if (strcmp(profile.name, "None") == 0)
                {
                    int make;
                    printf("\nNo profile found. Do you want to create a new profile? (1 = Yes, 2 = No): ");
                    make = inputi();
                    if (make == 1)
                    {
                        editprofile();
                    }
                }

                printf("1. View Profile\n");
                printf("2. Edit Profile\n");
                printf("3. Delete Profile\n");
                printf("0. Back to Main Menu\n");
                printf("Enter choice: ");
                pchoice = inputi();
                if (pchoice == 1)
                {
                    showprofile();
                }
                else if (pchoice == 2)
                {
                    editprofile();
                }
                else if (pchoice == 3)
                {
                    deleteprofile();
                }
                else if (pchoice == 0)
                {
                    break;
                }
                else
                {
                    printf("Invalid choice.\n");
                }
            }
            break;
        }
        case 8:
            analyticsmenu();
            break;
        case 9:
            faultdiagnose();
            break;
        case 0:
            printf("\nExiting.Thank You For Using CAR ASSISTANT SYSTEM..\n");
            showThankYou();
            return 0;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    }
    return 0;
}