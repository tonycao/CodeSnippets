/*
Write a method to generate a random number between 1 and 7, given a method that generates a random number between 1 and 5 (i.e., implement rand7() using rand5()).

*/

int Rand7(){
    int x = ~(1<<31); // max int
    while(x > 21)
        x = 5 * (Rand5() - 1) + Rand5() // Rand25
    return x%7 + 1;
}
