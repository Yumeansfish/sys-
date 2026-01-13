#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct car{
    char* model;
    char* maker;
    char* driver;
    int hp;
    int price;
    struct car* next;
};

struct driver{
    char* name;
    char* team;
    struct driver* next;
};

struct team{
    char* name;
    struct team* next;
};

static struct car* head_car = NULL;
static struct driver* head_driver = NULL;
static struct team* head_team = NULL;



int check_empty(char* line)
{
    while(*line)
    {
        if(strchr(" \t\n\r",*line))line++;
        else return 0;
    }
    return 1;
}

void racing_delete()
{
    while(head_driver)
    {
        struct driver* tmp = head_driver->next;
        if(head_driver->name)free(head_driver->name);
        if(head_driver->team)free(head_driver->team);
        free(head_driver);
        head_driver = tmp;
    }
    while(head_car)
    {
        struct car* tmp = head_car->next;
        if(head_car->model)free(head_car->model);
        if(head_car->maker)free(head_car->maker);
        if(head_car->driver)free(head_car->driver);
        free(head_car);
        head_car = tmp;
    }
    while(head_team)
    {
        struct team* tmp = head_team->next;
        if(head_team->name)free(head_team->name);
        free(head_team);
        head_team = tmp;
    }
}

FILE* car_mode(FILE* fp)
{
    char line[1001];
    struct car* new = malloc(sizeof(struct car));
    new->model = NULL;
    new->driver= NULL;
    new->maker= NULL;
    new->hp = 0;
    new->price = 0;
    if(!new)return NULL;
    while(fgets(line,sizeof(line),fp))
    {
        char* eq= strchr(line,'=');
        if (eq==line)return NULL;
        if(check_empty(line))continue;
        else if(strncmp(line,"maker",5)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->maker = malloc(len+1);
            memcpy(new->maker,eq+1,len);
            new->maker[len] ='\0';
        }
        else if(strncmp(line,"model",5)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->model = malloc(len+1);
            memcpy(new->model,eq+1,len);
            new->model[len] ='\0';
        }
        else if(strncmp(line,"driver",6)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->driver= malloc(len+1);
            memcpy(new->driver,eq+1,len);
            new->driver[len] = '\0';
        }
        else if(strncmp(line,"hp",2)==0)
        {
            char* n_symbol = strchr(line,'\n');
            *n_symbol = '\0';
            new->hp = atoi(eq+1);
        }
        else if(strncmp(line,"price",5)==0)
        {
            char* n_symbol = strchr(line,'\n');
            *n_symbol = '\0';
            new->price = atoi(eq+1);
        }
        else if(strncmp(line,"#end",4)==0)
        {
            new->next = head_car;
            head_car = new;
            return fp;
        }
        else return NULL;
    }
    return NULL;
}

FILE* driver_mode(FILE* fp)
{
    char line[1001];
    struct driver* new = malloc(sizeof(struct driver));
    new->name= NULL;
    new->team = NULL;
    if(!new)return NULL;
    while(fgets(line,sizeof(line),fp))
    {
        if(check_empty(line))continue;
        char* eq = strchr(line,'=');
        if(eq==line)return NULL;
        if(strncmp(line,"team",4)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->team = malloc(len+1);
            memcpy(new->team,eq+1,len);
            new->team[len] = '\0';
        }
        else if(strncmp(line,"name",4)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->name = malloc(len+1);
            memcpy(new->name,eq+1,len);
            new->name[len] = '\0';
        }
        else if(strncmp(line,"#end",4)==0)
        {
            new->next = head_driver;
            head_driver = new;
            return fp;
        }
        else return NULL;
    }
    return NULL;
}

FILE* team_mode(FILE* fp)
{
    char line[1001];
    struct team* new = malloc(sizeof(struct team));
    new->name = NULL;
    if(!new)return NULL;
    while(fgets(line,sizeof(line),fp))
    {
        char* eq = strchr(line,'=');
        if(eq==line)return NULL;
        if(check_empty(line))continue;
        else if(strncmp(line,"name",4)==0)
        {
            int len = strchr(line,'\n')-eq-1;
            new->name = malloc(len+1);
            memcpy(new->name,eq+1,len);
            new->name[len] = '\0';
        }
        else if(strncmp(line,"#end",4)==0)
        {
            new->next = head_team;
            head_team = new;
            return fp;
        }
        else return NULL;
    }
    return NULL;
}



int racing_init(const char* f)
{
    racing_delete();
    int count = 0;
    FILE* fp = fopen(f,"r");
    if(!fp)
    {
        return -1;
    }
    char line[1001];
    while(fgets(line,sizeof(line),fp))
    {
        //check_empty
        if(check_empty(line))continue;

        //#car
        if(strncmp(line,"#car",4)==0)
        {
            count++;
            fp = car_mode(fp);
            if(!fp)
            {
                racing_delete();
                return -1;
            }

            
        }
        else if(strncmp(line,"#driver",7)==0)
        {
            count++;
            fp = driver_mode(fp);
            if(!fp)
            {
                racing_delete();
                return -1;
            }
        }
        else if(strncmp(line,"#team",5)==0)
        {
            count++;
            fp =team_mode(fp);
            if(!fp)
            {
                racing_delete();
                return -1;
            }
        }
        else continue;
    }
    fclose(fp);
    return count;
}

unsigned count_cars(const char*model,const char* maker,const char* driver,
const unsigned hp,const unsigned price)
{
    struct car* itr = head_car;
    int count = 0;
    while(itr)
    {
        int match = 1;
        if(model)
        {
            if(!itr->model)match = 0;
            else if(strcmp(model,itr->model)!=0)match = 0;
        }
        if(maker)
        {
            if(!itr->maker)match =0;
            else if(strcmp(maker,itr->maker)!=0)match = 0;
        }
        if(driver)
        {
            if(!itr->driver)match = 0;
            else if(strcmp(driver,itr->driver)!=0)match = 0;
        }
        if(hp&&itr->hp!=hp)match = 0;
        if(price&&itr->price!=price)match =0;
        if(match)count++;
        itr = itr->next;
    }
    return count;
}

unsigned count_drivers(const char* name,const char* team)
{
    struct driver* itr = head_driver;
    int count = 0;
    while(itr)
    {
        int match = 1;
        if(name)
        {
            if(!itr->name)match =0;
            else if(strcmp(name,itr->name)!=0)match = 0;
        }
        if(team)
        {
            if(!itr->team)match = 0;
            else if(strcmp(team,itr->team)!=0)match=0;
        }
        if(match)count++;
        itr=itr->next;
    }
    return count;
}

unsigned get_teams()
{
    struct team* itr=head_team;
    int count = 0;
    while(itr)
    {
        count++;
        itr=itr->next;
    }
    return count;
}
