#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) 
{
    int serialize_state = serialize(state);
    insert_at_tail(&(q->data), serialize_state);  
    printf("inside enqueue\n"); 
}

struct game_state dequeue(struct queue *q) 
{ 
    if(q->data.head == NULL)
    {
        return (struct game_state){0}; 
    }
    int remove = remove_from_head(&(q->data));
    struct game_state dequeue = deserialize(remove);

    return dequeue;
}
    
static int final_state(struct game_state * current)
{
    static int num = 1;
    static int final_check = 0;

    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            if(current -> tiles[row][col] == num)
            {
                num++;
            }
            break;
        }
    }

    if(num == 15 && (current -> tiles[4][4] == 0))
    {
        final_check++;
    }

    return final_check;
}

static int not_visited (struct queue *visited, int move)
{
    struct list_node * temp = visited -> data.head;

    while(temp != NULL)
    {
        if(temp -> value == move)
        {
            return 0;
        }
        temp = temp -> next;
    }
    return 1;
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q;
    q.data.head = NULL;
    enqueue(&q, start);

    struct queue visited;
    visited.data.head = NULL;
    enqueue(&visited, start);

    while(!(q.data.head == NULL))
    {
        printf("move\n");
        struct game_state cur = dequeue(&q);
        if(final_state(&cur)) 
        {
            printf("final state true\n");
            return cur.num_steps;
        }
        else
        {
            printf("move part 2\n");
            struct game_state move = cur;
            if(cur.empty_row > 0)
            { 
                move_up(&move); 
                int move_up_serialized = serialize(move);
                if(not_visited(&visited, move_up_serialized))
                {
                    enqueue(&q, move);
                    enqueue(&visited, move);
                }
            }

            if (cur.empty_row < 3)
            { 
                move_down(&move); 
                int move_down_serialized = serialize(move);
                if(not_visited(&visited, move_down_serialized))
                {
                    enqueue(&q, move);
                    enqueue(&visited, move);
                }
            }

            if(cur.empty_col > 0)
            { 
                move_right(&move);
                int move_right_serialized = serialize(move);
                if(not_visited(&visited, move_right_serialized))
                {
                    enqueue(&q, move);
                    enqueue(&visited, move);
                }
            }

            if(cur.empty_col < 3)
            {
                move_left(&move);
                int move_left_serialized = serialize(move);
                if(not_visited(&visited, move_left_serialized))
                {
                    enqueue(&q, move);
                    enqueue(&visited, move);
                }
            }
        }
    }
    return -1; 
}
