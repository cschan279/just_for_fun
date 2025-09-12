use std::io;

use rand::Rng;
use rand::rng;

fn main() {
    println!("Guess the number!");
    let mut secret_range_min = 1;
    let mut secret_range_max = 100;
    let mut guess_value :u8;
    let mut rng = rng();
    let secret_number = rng.random_range(secret_range_min..=secret_range_max);

    loop {
        println!("Please input your guess[{secret_range_min}-{secret_range_max}].");

        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        guess_value = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        if guess_value < secret_range_min || guess_value > secret_range_max {
            println!("Please input a number between {secret_range_min} and {secret_range_max}.");
            continue;
        }

        if guess_value < secret_number {
            println!("Too small!");
            secret_range_min = guess_value + 1;
        } else if guess_value > secret_number {
            println!("Too big!");
            secret_range_max = guess_value - 1;
        } else {
            println!("You win!");
            break;
        }
    }
    
}