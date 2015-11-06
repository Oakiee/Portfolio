/* * * * * * * * * * * * * * * * * * * * *
Location.cs

Amanda Oyakawa
9/12/15

Overview:
        This is the abstract class to define locations in the game.

Variables:
        protected string OwnerName - The NPC's Name
        protected string TownName - The Town Name of this location
        protected string PlaceName - name of the place
        private bool _finished - are we still at this location? or did we leave it? 
            public bool Finished - property
        protected Dictionary<string, Item> ItemsHere - What items can be found here? 
        public Item SelectItem() - returns an item that the user selected 


Defined Methods:
        public void RemoveItem(Item item) - removes this item from the location
        public void ListItems() - Lists out all the items at this location
        public Item SelectItem() - returns an item the player selected (given the index on the ListItem method) the user may also view their inventory or exit the area from this script
        public void PlaceIntro() - just a little introduction of the place, a little description

* * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;
using PickersRPGBLL.Items;

namespace PickersRPGBLL.Locations
{
    public abstract class Location
    {
        protected string OwnerName;
        protected string TownName;
        public string PlaceName;
        protected string Description;
        private bool _finished;

        public bool Finished 
        {
            get {return _finished;}
            protected set { _finished = value; }

        }

        protected List<Item> ItemsHere;

        public void RemoveItem(Item item)
        {
            ItemsHere.Remove(item);
        }

        public void PlaceIntro()
        {
            Console.Clear();
            Console.WriteLine("You travel to {0} in {1} and are greeted by {2} at the door", PlaceName, TownName,
                OwnerName);
            Console.WriteLine("\n{0}\n\n",Description);
        }

        public void ListItems()
        {
            Console.WriteLine("\n {0}", PlaceName);
            Console.WriteLine("------------------------------------------");
            Console.WriteLine("\nThere are many items strewn about, but these are the ones that catch your eye:\n");
            int i = 1;
            foreach (var item in ItemsHere)
            {
                //only show the buyfor price if the player has looked closer at the item (and therefore the owner gave a price)
                if (item.FirstInquire)
                    Console.WriteLine("   {0} - {1}", i, item.Name);
                else if (item.WillingToSell)
                    Console.WriteLine("   {0} - {1} - {2}", i, item.Name, "$" + item.BuyFor);
                else
                    Console.WriteLine("   {0} - {1}", i, item.Name);
                i++;
            }
            
        }

        public Item SelectItem(Player player)
        {

            int value;
            bool valid;

            //when you hit q to quit but decide against it, loop to the beginning again but don't print the invalid error message
            bool skipErrorMessage = false;

            do
            {
                ListItems();
                Console.WriteLine("\n\n   Please enter one of the following: \n" +
                              "   # - the item you'd like a closer look at (see above numbers) \n" +
                              "   Q - quit (leave this location)\n" +
                              "   I - inventory\n ");
                var answer = Console.ReadLine();
                if (answer.ToUpper() == "I")
                {
                    player.DisplayInventory();
                    skipErrorMessage = true;
                }
                if (answer.ToUpper() == "Q")
                {
                    bool valid2;
                    do
                    {
                        Console.Write("Are you sure you want to leave this location? (Y/N): ");
                        var answer2 = Console.ReadLine();

                        //exit the location
                        if (answer2.ToUpper() == "Y")
                        {
                            valid2 = true;
                            _finished = true;
                            //just a random item to return and get out of the function
                            return new Fred();
                        }
                        else if (answer2.ToUpper() == "N")
                        {
                            valid2 = true;
                            Console.Clear();
                            Console.WriteLine("Change your mind? No problem.");
                            skipErrorMessage = true;
                        }
                        else
                        {
                            valid2 = false;
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine("I'm sorry, that was an invalid input, please enter \"y\" for Yes or \"n\" for No");
                            Console.ResetColor();
                        }
                    } while (!valid2); 

                }

                valid = Int32.TryParse(answer, out value);

                if (!valid && skipErrorMessage == false)
                {
                    Console.Clear();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("That wasn't a number.\n");
                    Console.ResetColor();
                }

                else if ((value > ItemsHere.Count() || value <= 0) && skipErrorMessage == false)
                {
                    Console.Clear();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("That was an invalid number, please try again.\n");
                    Console.ResetColor();
                    valid = false;
                }

            } while (!valid);

            return ItemsHere[value - 1];
        }

    }
}
