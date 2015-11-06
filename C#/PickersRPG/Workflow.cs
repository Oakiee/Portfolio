/* * * * * * * * * * * * * * * * * * * * *
Workflows.cs

Amanda Oyakawa
9/12/15

Overview:
        This script is the will call all the necessary functions that comprise the game, in the order 
        that they need to be called. 

Variables:

Defined Methods:
        public void Visit(Player player, Location location ) - Defines the loop for each location visit and what happens at each location
        public void FinishGame(Player player) - end screen that displays each item the user bought, how much it was resold for, along with total scores. 
        public void Execute() - call this function to play through the game
        public void Beginning(Player player) - this gives the player information about how to play the game, how much money they have, and the number of locations they will visit

* * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using PickersRPGBLL;
using PickersRPGBLL.Items;
using PickersRPGBLL.Locations;


namespace PickersRPG
{
    public class Workflow : IGameWorkFlow
    {
        public void Execute()
        {

            var player = new Player(300);

            player.AskName();
            Beginning(player);

            foreach (var location in player.AllLocations)
            {
                Visit(player, location);
            }

            FinishGame(player);

        }

        public void Beginning(Player player)
        {
            Console.WriteLine("\n{0}, you ever happen to hear of \"Off-Roading\"? ", player.Name);
            Console.WriteLine("I ask because that's what we will be doing today!\"Off-Roading\" means that \nwe will travel around to different locations and try to find cool " +
                              "antiques \nand collectibles that we can resell in the shop. I'll let you hold the \nreigns, I want " +
                              "to see how you do. At the end of the day we will check out \n" +
                              "the re-sale value of every item in your haul and see how you did! \nWell you ready?\n\n");

            Console.Write("Here is your budget for today: ");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("${0}", player.PlayerWallet.Cash);
            Console.ResetColor();
            Console.WriteLine("\nPlease keep in mind we have {0} locations for you to visit today!", player.AllLocations.Count);

            Console.WriteLine("\nPress any key to hit the road and get started!");
            Console.ReadKey();
            Console.Clear();
        }

        public void Visit(Player player, Location location)
        {
            location.PlaceIntro();

            do
            {
                var item = location.SelectItem(player);

                if (!location.Finished)
                    item.DisplayItem(player, location);

            } while (!location.Finished);

        }

        public void FinishGame(Player player)
        {
            Console.Clear();

            if (player.PlayerItems.Count == 0)
            {
                Console.WriteLine("Why didn't you buy anything? I think you missed the point!");
            }
            else
            {
                Console.WriteLine(
                    "You just finished your first \"Off-Roading\" haul! Let's see how you did, \nI went ahead and researched what each item is approximately worth...\n");
                Console.WriteLine("--------------------------------------------------------\n\n");
                Console.WriteLine("{0, 15}{1,25}{2, 18}{3,8}\n", "Name", "Bought for", "Can be sold for", "Profit");

                decimal totalMoneySpent = 0;
                decimal totalMoneyEarned = 0;

                foreach (var item in player.PlayerItems)
                {
                    var itemOutput = String.Format("{0, 20}{1, 15}{2, 15}{3,15}\n\n", item.Name, item.BuyFor, item.SellFor, item.SellFor - item.BuyFor);

                    if (item.BuyFor < item.SellFor)
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.WriteLine(itemOutput);
                        Console.ResetColor();
                    }

                    else if (item.BuyFor > item.SellFor)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine(itemOutput);
                        Console.ResetColor();
                    }
                    //if equal keep white
                    else
                    {
                        Console.WriteLine(itemOutput);
                    }

                    totalMoneySpent += item.BuyFor;
                    totalMoneyEarned += item.SellFor;
                }

                Console.WriteLine("--------------------------------------------------------");

                decimal profit = totalMoneyEarned - totalMoneySpent;

                Console.WriteLine("{0, 20}{1, 15}{2, 15}{3,15}\n\n", "Totals:", totalMoneySpent,

                    totalMoneyEarned, profit);


                if (profit > 0)
                {
                    Console.WriteLine("You turned a profit! Great job!");
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("\nYou made ${0}!", profit);
                    Console.ResetColor();
                }
                else if (profit == 0)
                {
                    Console.WriteLine(
                        "You managed to break even! So, you didn't lose anything and you had fun? \nHopefully you learned something for next time!");
                }
                else
                {
                    Console.WriteLine("Well, looks like you went in the red.");
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("\nYou lost ${0}.",Math.Abs(profit));
                    Console.ResetColor();
                    Console.WriteLine("\nMaybe you should phone a friend for help in the field next time?");
                }
            }

            Console.WriteLine("Press any key to see explanations to the resell prices");
            Console.ReadKey();

            ResellExplanations(player);

            Console.WriteLine("Press Enter to exit the game.");
            Console.ReadLine();


        }

        private void ResellExplanations(Player player)
        {

            Console.WriteLine("\n\n");
            foreach (var item in player.PlayerItems)
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("{0} ({1:c}) - {2}", item.Name, item.SellFor, item.ResellExplanation);
                Console.WriteLine("\n\n");
                Console.ResetColor();

                Console.WriteLine("Press enter to continue...");
                Console.ReadLine();
            }
        }

    }
}
