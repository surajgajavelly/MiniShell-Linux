//

#include "main.h"

// Insert a new process node at the head
void insert_jobs_to_list(job_list **process_head) 
{
    job_list *new_node = (job_list *)malloc(sizeof(job_list));
    if (!new_node) {
        perror("Failed to allocate memory for new process");
        return;
    }

    new_node->pid = child_pid;
    strcpy(new_node-> input_string, input_string);
    new_node->next = *process_head;

    if (*process_head == NULL) 
    {
        *process_head = new_node;
    } 
    else 
    {
        new_node->next = *process_head;
        *process_head = new_node;
    }
    return;
}

// Delete a process
void delete_jobs_from_list(job_list **process_head) 
{
   if (process_head == NULL || *process_head == NULL) 
   {
       return;
   }

    job_list *curr = *process_head;
    *process_head = curr->next;
    free(curr);
    return;
}

// Print all jobs in the list
void print_jobs(job_list *process_head)
{
    job_list *curr = process_head;
    int job_id = 1;

    while (curr != NULL) {
        printf("[%d] PID: %d\tCMD: %s\n", job_id, curr->pid, curr->input_string);
        curr = curr->next;
        job_id++;
    }

    if (job_id == 1) {
        printf("No jobs\n");
    }
}
