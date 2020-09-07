#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //para cada candidato
    for (int i = 0 ; i < MAX ; i++)
    {
        //se o nome do candidato for igual a algum dos candidatos
        if (candidates[i].name != 0)
        {
            if (strcmp(candidates[i].name, name) == 0)
            {
                //update total votes to the candidate in the struct
                candidates[i].votes++;
                return true;
            }
        }
        
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string winners[9];
    int higherNVotes = 0;
    int winnersQuantity = 0;
    // TODO
    //para cada candidato
    for (int i = 0 ; i < MAX ; i++)
    {
        //se o numero de votos do candidato for maior que a variavel higherNVotes
        if (candidates[i].votes > higherNVotes)
        {
            //atualiza a variavel higherNVotes
            higherNVotes = candidates[i].votes;
            //limpa o array de vencedores e coloca o novo vencedor
            memset(winners, 0, sizeof winners);
            winnersQuantity = 0;
            winners[winnersQuantity] = candidates[i].name;
            
        }
        //se o numero for igual, coloca o nome do candidato na proxima posição
        else if (candidates[i].votes == higherNVotes)
        {
            winnersQuantity++;
            winners[winnersQuantity] = candidates[i].name;
        }
    }
    
    for (int i = 0; i <= winnersQuantity; i++)
    {
        printf("%s\n", winners[i]);
    }
    
    return;
}

