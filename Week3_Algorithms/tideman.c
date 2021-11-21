#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int end, int start);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        // If the voted candidate name is found,input vote for candidate
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Set all elements to false

    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Initialize pair_count
    pair_count = 0;

    // Look for highest count for each row
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // The matrix of prerefences should be symmetrical (diagonally)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO


    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // Store the current pair and the next pair
            int sort_i = preferences[pairs[i].winner][pairs[i].loser];
            int sort_j = preferences[pairs[j].winner][pairs[j].loser];

            // Swap pairs if the next iter pair has a larger vote
            if (sort_i < sort_j)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Initiliaze whole locked as false
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            locked[i][j] = false;
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        // Check if the loser beats the winner somehow as prerecorded
        if (!cycle_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }



    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Look for candidate whose column consist of only falses
    for (int i = 0; i < candidate_count; i++)
    {
        // Count falses
        int count = 0;

        // Iterate through the rows of the locked column and count falses. If all false (count = candidates quantity), this candidate must be or
        // one of the winners
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count++;

                if (count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }


        }
    }

    return;
}

bool cycle_check(int end, int start)
{
    // Recursive exit condition. If beginning equals start means there is a cycle
    if (end == start)
    {
        return true;
    }

    // Cycle through
    for (int i = 0; i < candidate_count; i++)
    {
        // Check locked pair graph for
        if (locked[end][i])
        {
            // Checks if cycle present. Recursive entry/cycle condition.
            if (cycle_check(i, start))
            {
                return true;
            }
        }
    }
    return false;
}