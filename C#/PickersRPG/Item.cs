/* * * * * * * * * * * * * * * * * * * * *
Item.cs

Amanda Oyakawa
9/12/15

Overview:
        This is an abstract class Item to define what fields the items that inherit from it will have

Variables:
        *** Note: I don't know if it is kosher, but for variables that shouldn't be showing up anywhere, such as the Thanks string (message after you make a purchase)
        for an object that can't be bought, then I put the string = ".NOPE" so I notice that it shouldn't be showing up should it appear. 
        ((The anecdotal reason for .NOPE is my friend received a ".Nope" error when we were working on c++ and to this day I have no idea what 
        that meant nor does a google search yield anything still. I got excited when I looked it up and saw someone post about it on imgur, but then realized
        it was her haha...))

        protected string Name - Name of item
        protected decimal BuyFor - How much can the player buy this item from the NPC for?
        protected decimal SellFor - How much is this item actually worth? Tallied at the end of the game to determine score
        protected string Description - description of the item
        protected bool WillingToSell - Is the NPC willing to part with this item? The player can only buy an item if so.
        protected bool FirstInquire - Is this the first time you look at an item? If it's past the 1st time you'll get an abridged response upon revisiting an item.
        protected string FirstLook - What is printed out to the console the first time looking closer at this item?
        protected string LookAgain - What is printed out to the console after the first time looking closer at this item? 
        protected string Thanks - What does the NPC say if you buy the item?
        public string ResellExplanation - why did this item sell for as much as it did? 
        protected bool FriendCalled - Have you called a friend yet or not for this item? Can only call a friend once per item.

Defined Methods:

        public void DisplayItem - Writes out all of the associated information about an item. 
        public void BuyItem(Player player, Location location) - shows the user the cost of the item and their cash and their remaining cash should they buy the item. If they answer Yes they would, then the item is added to the player's inventory and deleted from the location's items list. They can back down and say no if they'd like to

* * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;
using PickersRPGBLL.Locations;

namespace PickersRPGBLL.Items
{
    public abstract class Item
    {
        public string Name { get; set; }
        public decimal BuyFor { get; set; }
        public decimal SellFor { get; set; }
        protected string Description { get; set; }
        public bool WillingToSell { get; set; }
        public bool FirstInquire { get; set; }
        protected string FirstLook { get; set; }
        protected string LookAgain { get; set; }
        protected string Thanks { get; set; }
        public string ResellExplanation { get; set; }
        protected bool FriendCalled { get; set; }

        public void DisplayItem(Player player, Location location, bool showBuy = true)
        {
            Console.Clear();
            Console.WriteLine("\n {0} - {1}", location.PlaceName, Name);
            Console.WriteLine("------------------------------------------");
            Console.WriteLine("\n{0}\n", Description);
            if (FirstInquire)
            {
                Console.WriteLine("\"{0}\"\n", FirstLook);
                FirstInquire = false;
            }
            else
            {
                Console.WriteLine("\"{0}\"\n", LookAgain);
            }

            if (WillingToSell && showBuy)
            {
                Console.WriteLine("The going price is: ${0}\n\n", BuyFor);
                BuyItem(player, location);
            }

            else if (!WillingToSell)
            {
                Console.WriteLine("Doesn't look like they are willing to part with this item, better keep looking.\n");
                Console.WriteLine("\nPress any key to continue.");
                Console.ReadKey();
                Console.Clear();
            }

        }

        public void BuyItem(Player player, Location location)
        {

            bool valid;
            do
            {
                Console.WriteLine("${0, 5} - Your Cash", player.PlayerWallet.Cash);
                Console.WriteLine("${0, 5} - Price", BuyFor);
                Console.WriteLine("________");
                Console.WriteLine("${0, 5} - Your cash if you purchase {1}", player.PlayerWallet.Cash - BuyFor, Name);
                if (FriendCalled == false)
                {
                    Console.WriteLine(
                        "\n\nWould you like to purchase this item now? (Y/N) \nOr perhaps you want to phone a friend? (F)\nKeep in mind you can always look at this item again.");
                }
                else
                {
                    Console.WriteLine(
       "\n\nWould you like to purchase this item now? (Y/N) \nKeep in mind you can always look at this item again.");
                }
              
                var answer = Console.ReadLine();

                if (answer.ToUpper() == "Y")
                {

                    bool canBuy = player.PlayerWallet.RemoveCash(BuyFor);
                    if (canBuy)
                    {

                        valid = true;
                        Console.Clear();
                        Console.WriteLine("{0}\n", Thanks);

                        player.AddItem(this);
                        location.RemoveItem(this);

                        player.DisplayInventory();

                    }
                    else
                    {
                        Console.Clear();
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("\nI'm sorry, it looks like you don't have enough money for that purchase.");
                        Console.ResetColor();
                        return;
                    }

                }
                else if (answer.ToUpper() == "N")
                {
                    valid = true;
                    Console.Clear();
                }

                else if (answer.ToUpper() == "F" && FriendCalled == false)
                {
                    Console.WriteLine();
                    var friend = new PhoneAFriend();
                    string friendAnswer = friend.Call();
                    valid = false;
                    FriendCalled = true;
                    Console.WriteLine("{0}\n\nAlright, your friend give you some good pointers? \nPress any key to continue.", friendAnswer);
                    Console.ReadKey();
                    Console.Clear();
                    DisplayItem(player, location, false);

                }

                else
                {
                    valid = false;
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("I'm sorry, that was an invalid input, please enter \"y\" for Yes or \"n\" for No");
                    Console.ResetColor();          
                }
            

        } while (!valid);


        }

    }
}
