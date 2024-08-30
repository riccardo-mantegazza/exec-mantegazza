#include <stdio.h>
#include <setjmp.h>

extern jmp_buf env;

void to_be_interrupted () {
    printf ("Mr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much.");

    //Decide where to interrupt
    if (setjmp(env) == 0) printf ("They were the last people you’d expect to be involved in anything strange or mysterious, because they just didn’t hold with such nonsense.\nMr. Dursley was the director of a firm called Grunnings, which made drills. He was a big, beefy man with hardly any neck, although he did have a very large mustache. Mrs. Dursley was thin and blonde and had nearly twice the usual amount of neck, which came in very useful as she spent so much of her time craning over garden fences, spying on the neighbors. The Dursleys had a small son called Dudley and in their opinion there was no finer boy anywhere.");
    else printf ("Execution interrupted");

}