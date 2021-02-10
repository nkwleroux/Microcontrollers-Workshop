/*
 * DeelB7A.c
 *
 * Created: 06/2/2021 1:45:59 PM
 * Author : Nic
 *
 * Dit opdracht is niet af.
 */ 

#define F_CPU 8e6

#include <avr/io.h>

int start_state();
int s1_state();
int s2_state();
int s3_state();
int end_state();
 
 int (* state[])(void) = { start_state, s1_state, s2_state, s3_state, end_state };
 enum state_codes { start, s1, s2, s3, end };

enum event_codes { pd7, pd6, pd5 };

#define ENTRY_STATE start
#define EXIT_STATE end

struct transition {
	enum state_codes src_state;
	enum event_codes   ret_code;
	enum state_codes dst_state;
};

struct transition state_transitions[] = {
	{entry, ok,     foo},
	{entry, fail,   end},
	{foo,   ok,     bar},
	{foo,   fail,   end},
	{foo,   repeat, foo},
	{bar,   ok,     end},
	{bar,   fail,   end},
	{bar,   repeat, foo}};

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

