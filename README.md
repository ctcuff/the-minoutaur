# Minotaur's Birthday Party

## Running the Code:

Assuming you're running on a Unix-like system, you'll need to have [make](https://www.gnu.org/software/make/) installed

- In the root directory, run `make`. This will compile `birthday_party.cpp` and `crystal_vase.cpp` into executables located in the `out` directory.
- Now, you can run either `./out/birthday_party` or `./out/crystal_vase`
- **NOTE**: Both programs define a constant called `NUM_GUESTS`. You can update this variable and recompile to test the programs on larger inputs.

## The Problem

The Minotaur invited N guests to his birthday party. When the guests arrived, he made the following announcement.

The guests may enter his labyrinth, one at a time and only when he invites them to do so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When a guest finds a way out of the labyrinth, he or she may decide to eat the birthday cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find the cupcake plate empty and may request another cupcake by asking the Minotaur's servants. When the servants bring a new cupcake the guest may decide to eat it or leave it on the plate.

The Minotaur's only request for each guest is to not talk to the other guests about her or his visit to the labyrinth after the game has started. The guests are allowed to come up with a strategy prior to the beginning of the game. There are many birthday cupcakes, so the Minotaur may pick the same guests multiple times and ask them to enter the labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have had the chance to enter his labyrinth. To do so, the guests must announce that they have all visited the labyrinth at least once.

Now the guests must come up with a strategy to let the Minotaur know that every guest entered the Minotaur's labyrinth. It is known that there is already a birthday cupcake left at the labyrinth's exit at the start of the game. How would the guests do this and not disappoint his generous and a bit temperamental host?

Create a program to simulate the winning strategy (protocol) where each guest is represented by one running thread. In your program you can choose a concrete number for N or ask the user to specify N at the start.

## The Solution

- Create N threads. The first thread will be responsible for counting how many times it replaced the cupcake, while the other N - 1 threads will eat the cupcake (only once though).
- Each thread will wait until they're randomly selected. When it's their turn, the thread "eats" the cupcake, then marks itself as "satisfied" so it doesn't greedily eat another cupcake.
- Once every thread has gotten a chance to eat the cupcake and the counter thread counts N guests, the program terminates.

Small side note: this implementation relies on randomness so the time complexity for this is complicated. There's no way to know for sure that running this program will ensure that N guests are chosen in O(n) time or O(n!) time.

# Minotaur's Crystal Vase

## The Problem

The Minotaur decided to show his favorite crystal vase to his guests in a dedicated showroom with a single door. He did not want many guests to gather around the vase and accidentally break it. For this reason, he would allow only one guest at a time into the showroom. He asked his guests to choose from one of three possible strategies for viewing the Minotaur's favorite crystal vase:

1. Any guest could stop by and check whether the showroom's door is open at any time and try to enter the room. While this would allow the guests to roam around the castle and enjoy the party, this strategy may also cause large crowds of eager guests to gather around the door. A particular guest wanting to see the vase would also have no guarantee that she or he will be able to do so and when.

2. The Minotaur's second strategy allowed the guests to place a sign on the door indicating when the showroom is available. The sign would read "AVAILABLE" or "BUSY." Every guest is responsible to set the sign to "BUSY" when entering the showroom and back to "AVAILABLE" upon exit. That way guests would not bother trying to go to the showroom if it is not available.

3. The third strategy would allow the quests to line in a queue. Every guest exiting the room was responsible to notify the guest standing in front of the queue that the showroom is available. Guests were allowed to queue multiple times.

Which of these three strategies should the guests choose? Please discuss the advantages and disadvantages.

Implement the strategy/protocol of your choice where each guest is represented by 1 running thread. You can choose a concrete number for the number of guests or ask the user to specify it at the start.

## The Solution

This solution is similar to that of the birthday party problem except that there is no counting thread.

This solution uses the second strategy of waiting until the room is available before a thread can enter. An advantage of this is simplicity. We don't care about managing a queue or implementing a complex custom lock, all we need is a simple mutex and a status variable. It should be noted that there's no way to guarantee any type of execution order for this implementation since threads access the vase on a first come first served basis.

Here's how it works:
- Create N threads and an unordered set (initially empty) that keeps track of what threads have already seen the vase.
- When a thread "enters" the room, it sets the status of the room to `busy`, admires the vase for a random amount of time, then sets the status back to `available`.
- After the thread has admired the vase, it adds its ID to an unordered set so that it doesn't look at the vase more than once.
