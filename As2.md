Problem
The Minotaur invited N guests to his birthday party. When the guests arrived, he made 
the following announcement. 
The guests may enter his labyrinth, one at a time and only when he invites them to do 
so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When 
a guest finds a way out of the labyrinth, he or she may decide to eat the birthday 
cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find 
the cupcake plate empty and may request another cupcake by asking the Minotaur’s 
servants. When the servants bring a new cupcake the guest may decide to eat it or leave 
it on the plate. 
The Minotaur’s only request for each guest is to not talk to the other guests about her or 
his visit to the labyrinth after the game has started. The guests are allowed to come up 
with a strategy prior to the beginning of the game. There are many birthday cupcakes, so 
the Minotaur may pick the same guests multiple times and ask them to enter the 
labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have 
had the chance to enter his labyrinth. To do so, the guests must announce that they have 
all visited the labyrinth at least once. 
Now the guests must come up with a strategy to let the Minotaur know that every guest 
entered the Minotaur’s labyrinth. It is known that there is already a birthday cupcake left 
at the labyrinth’s exit at the start of the game. How would the guests do this and not 
disappoint his generous and a bit temperamental host? 
Create a program to simulate the winning strategy (protocol) where each guest is 
represented by one running thread. In your program you can choose a concrete number 
for N or ask the user to specify N at the start.


Answer:

Approach
/*
Guest  random selected
    Guest ask for cupcake
        Cupcake is unavailable
                Cupcake is resupplied
                    Guest eats cupcake
                    Guest doesn't eat cupcake
        Cupcake is available
            Guest eats cupcake
            Guest doesn't eat cupcake
    Guest doesn't ask for cupcake

*/

Create N threads to each represent a guest

    For each thread record when they are randomly chosen and record if they happen to eat a cupcake




Problem:
The Minotaur decided to show his favorite crystal vase to his guests in a dedicated 
showroom with a single door. He did not want many guests to gather around the vase 
and accidentally break it. For this reason, he would allow only one guest at a time into 
the showroom. He asked his guests to choose from one of three possible strategies for 
viewing the Minotaur’s favorite crystal vase: 
1) Any guest could stop by and check whether the showroom’s door is open at any time 
and try to enter the room. While this would allow the guests to roam around the castle 
and enjoy the party, this strategy may also cause large crowds of eager guests to gather 
around the door. A particular guest wanting to see the vase would also have no 
guarantee that she or he will be able to do so and when. 
2) The Minotaur’s second strategy allowed the guests to place a sign on the door 
indicating when the showroom is available. The sign would read “AVAILABLE” or 
“BUSY.” Every guest is responsible to set the sign to “BUSY” when entering the 
showroom and back to “AVAILABLE” upon exit. That way guests would not bother trying 
to go to the showroom if it is not available. 
3) The third strategy would allow the quests to line in a queue. Every guest exiting the 
room was responsible to notify the guest standing in front of the queue that the 
showroom is available. 

Guests were allowed to queue multiple times. 
Which of these three strategies should the guests choose? Please discuss the advantages 
and disadvantages. 
Implement the strategy/protocol of your choice where each guest is represented by 1 
running thread. You can choose a concrete number for the number of guests or ask the 
user to specify it at the start. 

Answer:
All the strategy implement a scheduler resmbling a FIFO scheduler with varying extra features

Strategy 1 is a basic simple fifo scheduer which  is easy to faciliate but a poor overall strategy.
The major downside is that one guest can hog the room and those guests who simply just wanted to pop in a get a quick glance  may end up
waiting for exoberant times

Strategy 2  most resembles the labrynth problem with the only major difference being the lack of a counter since 
guest don't reneter

Strategy 3 is similar to strategy 2 but requires the maintenance of a queue so it is harder to implement



Strategy 2 was chosen for the purpose of this program