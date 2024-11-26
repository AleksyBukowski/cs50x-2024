-- Keep a log of any SQL queries you execute as you solve the mystery.
-- first, we need to know which tables can we work with
.tables
-- then, we need to know what data we can access in the crime_scene_reports table
.scehma crime_scene_reports
-- then, we look for info about the day July 28, 2023, since that is when the crime took place
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2023;
-- we now know that the crime took place on Humphrey Street in a bakery at 10:35 am. We also know there were 3 witnesses - let's check the interviews for that date
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2023;
-- we know that the thief rode away with a car - and that we will most likely see that on the bakery's secureity footage around the 10th minute - we also know that he withdrew money on Leggett Street and that he made a call lasting less thana a minute. He most likely took a plane - the earliest flight the next day, meaning, 29th of July 2023.
-- let's check the bakery table now
.schema bakery_security_logs
-- and let's see the logs for 28th July of 2023
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023;
-- a lot of exits at around 10:15 am - we need to look for more info.
-- let's see the atm transactions
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street";
-- a lot of info here - let's look at accounts and then phone calls.
.schema accounts
.schema phone_calls
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023;
-- let's look at the earliest flight on the next day now - the 29th of July
.schema flights
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2023 ORDER BY hour ASC;
-- we now know that he escaped to an airport of an id 4 and that the flights id is 36.
-- let's look at the airports
SELECT * FROM airports;
-- we now know that the thief escaped to New York City.
-- let's look at passengers table now.
SELECT * FROM passengers WHERE flight_id = 36;
-- let's look at the people table now.
SELECT * FROM people;
-- now, we need to find the name of the person who has: attended the flight of id 36, left the bakery at around 10:15, called someone and talked for less less than a minute and withdrew money from an ATM the same day.
SELECT people.name, people.passport_number, people.phone_number FROM people JOIN passengers ON passengers.passport_number = people.passport_number WHERE passengers.flight_id = 36 AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND activity = "exit" AND minute BETWEEN 14 AND 25) AND people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2023 AND day = 28 AND month = 7) AND people.id IN (SELECT bank_accounts.person_id FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE atm_transactions.month = 7 AND atm_transactions.year = 2023 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw");
-- we now know that the thief is Bruce and his phone number is (367) 555-5533. Let's see who he called on 28th of July 2023 to see who was his accomplice - we also need to make sure to look for calls lasting less than 60 seconds..
SELECT * FROM phone_calls WHERE caller = "(367) 555-5533" AND day = 28 AND month = 7 AND year = 2023 AND duration < 60;
-- we now know that his accomplice's number is (375) 555-8161 since that is the receiver of the call. Let's look for his name now.
SELECT name FROM people WHERE phone_number = "(375) 555-8161";
-- we now know that the accomplice's name is Robin, which makes the entire mystery solved.
