import java.util.*;
import java.io.*;
/** Wordle
 * This program emulates the game wordle, wherein you have 6 chances to guess the right word based
 * on feedback given on each guess.
 * @author Aiden Thompson
 * @version 1.5
 */

public class Main {
    public static void main(String[] args) {
        Random rand = new Random ();
        Scanner stdin = new Scanner(System.in);

        ArrayList<String> words = new ArrayList<>();

        fill(words);

        String word = words.get(rand.nextInt(4499));

        System.out.println("You have six tries to guess a five-letter word.");

        System.out.println();

        for (int i = 0; i < 6; ++i){
            String guess = "";
            boolean valid = false;
            System.out.println("What is your guess? ");
            while (!valid){
                guess = stdin.next();
                if (words.contains(guess)){
                    valid = true;
                }
                else{
                    System.out.println("Sorry, either that word was spelled incorrectly, or it is " +
                            "not in my library. Please try again.");
                }
            }
            if (guess.equals(word)){
                System.out.println("Congratulations, you got it! ");
                break;
            }

            feedback(word, guess);

            if (i == 5){
                System.out.println("Sorry, you're out of guesses, you lose!");
            }
        }


    }

    public static void feedback(String word, String guess){
        for (int j = 0; j < 5; ++j){

            if (word.contains(Character.toString(guess.charAt(j)))){
                if (guess.charAt(j) == word.charAt(j)){
                    System.out.println("The " + guess.charAt(j) + " is right!");
                }
                else {
                    System.out.println("There is a " + guess.charAt(j) + " but not here.");
                }
            }
        }
    }

    public static void fill (ArrayList<String> words){
        Scanner fileIn;
        try {
            //fileIn = new Scanner("words.txt");
            fileIn = new Scanner(new File("words.txt"));
        }
        catch (FileNotFoundException e) {
            System.out.println("The file was not found, please try again");
            throw new RuntimeException(e);
        }

        while (fileIn.hasNext()) {
            words.add(fileIn.next());
        }
    }

}