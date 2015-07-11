#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    char ch;

    while ((ch = getopt(argc,argv,"adn")) != EOF)
        switch(ch){

        case 'a':
            printf("University is in Jaipur\n");
            break;
        case 'd':
            printf("Department is Electircal\n");
            break;
        case 'n':
            printf("Number of people are %d\n",324);
            break;
        default:
            fprintf(stderr,"Unknown option : %s\n","unknown");
            return 1;
        }
    //argc -= optind;
    //argv += optind;
    return 0;
}


