#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int rank, size, memberKey, data, num_errors;
    char port[MPI_MAX_PORT_NAME];
    char user[100];
    char msg[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data_test;
    //scanf("%d", &data_test);
    scanf ("%[^\n]%*c", msg);
            

    if(size != 3)
    {
        printf("This application is for 3 processors only. \n");

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Finalize();

        return 0; 
    }
    memberKey = rank % 3; //memberKey for 3 processors = 1, 2, 3
    

    //server
    if (rank == 0)
    {   
        MPI_Comm client;
        MPI_Status status;

        printf("0: opening ports.\n");fflush(stdout);
        MPI_Open_port(MPI_INFO_NULL, port);
        printf("opened port: <%s>\n", port);
        
        MPI_Send(port, MPI_MAX_PORT_NAME, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
       
        while (1)
        {
            MPI_Comm_accept(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &client);
            int again = 1;
            while(again)
            {
                MPI_Recv(msg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, client, &status);
                switch(status.MPI_TAG)
                {
                    case 0:
                    {
                        if(strchr(msg, '1') != NULL)
                        {
                            printf("[1]: %s", msg);
                            break;
                        }
                        else if(strchr(msg, '2') != NULL)
                        {
                            printf("[2]: %s", msg);
                            break;
                        }
                        else if(strchr(msg, '|') != NULL)
                        {
                            status.MPI_TAG = 1;
                            break;
                        }
                    }
                    case 1:
                    {
                        MPI_Comm_disconnect(&client);
                        MPI_Comm_free(&client);
                        MPI_Close_port(port);
                        again = 0;

                        printf("The program will now exit !!!\n");
                        MPI_Finalize();
                        return 0;
                    }
                    default:
                    {
                        printf("The program is broken. \n");
                        MPI_Abort(MPI_COMM_WORLD, 1);
                    }
                }
            }    
        }
    }

    //client
    else
    {   
        MPI_Comm server;
        MPI_Status status;

        MPI_Recv(port, MPI_MAX_PORT_NAME, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Comm_connect(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &server);
        
        int i = 0;
        
        
        {
            int tag = 0;
            //scanf ("%[^\n]%*c", msg);
            
            if(strchr(msg, '1') != NULL)
            {
                tag = 1;
            }
            MPI_Send(&msg, strlen(msg), MPI_CHAR, 0, tag, server);

            if(tag == 1)
            {
                MPI_Comm_disconnect(&server);
                i = 1;
                
            }            
        } 

        
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

