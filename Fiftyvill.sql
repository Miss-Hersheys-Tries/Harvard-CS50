-- The CS50 Duck has been stolen! The town of Fiftyville has called upon you to solve the mystery of the stolen duck. 
-- Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town with the
-- help of an accomplice. Your goal is to identify:
-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape
-- All you know is that the theft took place on July 28, 2023 and that it took place on Humphrey Street.

-- Log 1: Getting description from Date & Place of Theft
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Log 2: Getting security logs (license plate) from bakery parking
SELECT id, activity, license_plate, hour, minute FROM bakery_security_logs
WHERE day=28 AND month=7 AND hour=10;

-- Log 3: Getting names for corresponding license plates
SELECT people.id, people.name, people.license_plate FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND
bakery_security_logs.hour = 10;

-- ###########################################################################
-- SUSPECTS: 1.VANESSA 2.BRUCE 3.BARRY 4.LUCA 5.SOFIA 6.IMAN 7.DIANA 8.KELSEY
-- ###########################################################################

-- Log 4: Getting names of people who withdrew money from atm
SELECT people.name, atm_transactions.account_number, atm_transactions.amount
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28 AND
atm_transactions.atm_location = 'Leggett Street';

-- #########################################
-- SUSPECTS: 1.BRUCE 2.DIANA 3.IMAN 4.LUCA
-- #########################################

-- Log 5: Getting names of people who called for less than a minute
SELECT phone_calls.id, phone_calls.caller, phone_calls.receiver,
phone_calls.duration, people.name FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE month=7 AND day=28 AND duration<=60;

-- ###########################
-- SUSPECTS: 1.BRUCE 2.DIANA
-- ###########################

-- Log 6: Determining the earliest Flight
SELECT flights.id, flights.hour, flights.minute FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE flights.month=7 AND flights.day=29
ORDER BY hour, minute;

-- Log 7: Determining people who took the earliest flight 36 from Fiftyville
SELECT passengers.seat, people.name FROM passengers
JOIN people ON passengers.passport_number=people.passport_number
WHERE flight_id = 36;

-- ##################
-- THIEF = BRUCE
-- ##################

-- Log 8: Determining the accomplice from phone logs
SELECT name FROM people
WHERE phone_number =
(SELECT receiver FROM phone_calls
WHERE caller =
(SELECT phone_number FROM people
WHERE name = 'Bruce' AND day=28 AND month=7 AND duration<=60));

-- #####################
-- ACCOMPLICE = ROBIN
-- #####################

-- Log 9: Determining the city they escaped to
SELECT city FROM airports
WHERE id =
(SELECT destination_airport_id FROM flights
WHERE id = 36);

-- #####################
-- CITY = NEW YORK
-- #####################

-- ##############################################
-- ANSWERS
-- The THIEF is: Bruce
-- The city the thief ESCAPED TO: New York City
-- The ACCOMPLICE is: Robin
-- ##############################################
