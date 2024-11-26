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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count; // (added here by me)

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    voter_count = get_int("Number of voters: ");

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
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // loops through each rank
    for (int i = 0; i < candidate_count; i++) {
        // loops through each of the remaining, lower ranks
        for (int j = i+1; j < candidate_count; j++) {
            // if the r-th rank has the c-th candidate value
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // iterates for the i-th candidate
    for (int i = 0; i < candidate_count; i++) {
        // iterates for the j-th candidate
        for (int j = 0; j < candidate_count; j++) {
            // if the number of voters prefering i over j is highier than the opposite, i is declared the winner
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
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
    // selection sort looks through each pair
    for (int i = 0; i < pair_count; i ++) {
        // and then it compares it to the next pairs
        for (int j = i+1; j < pair_count; j++) {
            // switches them, if any of the next pairs difference is bigger than the i pair
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]){
                int temp_winner = pairs[i].winner;
                int temp_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp_winner;
                pairs[j].loser = temp_loser;
            }
        }
    }
    return;
}

bool cycle(int winner, int loser);
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // iterates through each pair (sorted in decreasing order of victory strength)
    for (int i = 0; i < pair_count; i++) {
        // if there's no cycle (yet?), then lock them
        if (!cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool cycle(int winner, int loser) {
    // if winner is the same as loser (finally must happen with recursion, if there is a cycle)
    if (winner == loser) {
        // return true => there is indeed a cycle
        return true;
    }

    // loop through each candidate
    for (int i = 0; i < candidate_count; i++) {
        // if our current recursion LOSER is the WINNER in another pair,
        // we know that he won against candidate i.
        // AND if cycle() [recursive call] between the current WINNER and the i, returns true;
        // that means, if a cycle exists, and we keep comparing our current WINNER (stays the same all the time)
        // with next candidates, we will finally realise that the same WINNER we kept all the time is
        // a LOSER in another pair, thus, there is a cycle (returns TRUE && TRUE => the entire function returns true
        // meaning that there is a cycle)
        if (locked[loser][i] && cycle(winner, i)) {
            return true;
        }
    }
    // realise, how this funtion will always return false on the 1st check, cause there aren't any locks yet
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // iterates through each candidate
    for (int i = 0; i < candidate_count; i++) {
        // at first, assumes that the candidate is untouched
        // (hasn't been locked by anyone)
        bool untouched = true;
        // iterates through each candidate
        for (int j = 0; j < candidate_count; j++) {
            // if ANYONE (j) is locked onto our candidate i (outer loop)
            if (locked[j][i]) {
                // then candidate i is no longer untouched, meaning, that he is not the winner
                // (he is not the source of the graph)
                untouched = false;
                break;
            }
        }
        // if the candidate i remained untouched (no one was locked onto him)
        // he is declared the winner.
        if (untouched) {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}
