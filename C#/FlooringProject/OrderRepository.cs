/* * * * * * * * * * * * * * * * * * * * *
OrderRepository.cs
Written by Andy Forthofer and Amanda Oyakawa

9/25/15

Overview: This is the class that deals with all of the data in the orders files. It can read in data and write to the file. 
        
Constructor: none
        
Variables:      private string FilePath - this is the path that you can set in order to read or write to/from a file of a certain name
                string FilePathErrorLogger = @"DataFiles\Errors.txt" - the error text file stays the same. Any errors caught within the OrderManager class are written here.

Defined Methods: public void CreateOrder(Order newOrder, DateTime date, bool writeHeader = false)
                        This function will call the necessary functions in order to 
                        write the new order to the text file. It takes  in the new order to be written, 
                        the date (which indicates which file) and the default parameter that is 
                        set to false which determines whether it will call the header to be written or not.
                 public void WriteHeader(StreamWriter writer)
                        This function writes the first header line for the file (when you are creating 
                        the first order in a new file this will be called)
                public void WriteOrder(Order newOrder)
                        This function literally writes the order out into the file. 
                public void DeleteOrder(int orderNumber, DateTime date)
                        This function will remove a particular order from the list of orders read in 
                        from a file. It will then call the overwrite function so that file has the new 
                        updated list.
               public int HighestOrderNumber(DateTime date)
                        returns the highest order number in a given file (determined by the date)
               public void SetFilePath(DateTime date)
                        This will take in a date and set the file path for the repo functions to work with
               public void CreateFile(DateTime date)
                        This is called when it is found that there isn't already a file at the given date-
                        so it then creates the file.  
                public List<Order> LoadOrders(DateTime date)
                        returns the full list of orders from a file at the given date.       
                 public bool FileExists(DateTime date)
                        returns true if the file exists given that date
                  public void ErrorLogger(string exception)
                        writes an error to the error file should an exception be caught
                                

* * * * * * * * * * * * * * * * * * * * * */
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using FlooringProgram.Models;

namespace FlooringProgram.Data
{
    public class OrderRepository
    {
        private string FilePath;
        string FilePathErrorLogger = @"DataFiles\Errors.txt";

        private List<State> states;

        private List<Product> products;

        public void CheckAndAddDirectory()
        {
           if (!Directory.Exists(@"DataFiles"))
           {
               Directory.CreateDirectory(@"DataFiles");
           }

            if (!Directory.Exists(@"TestOrders"))
            {
                Directory.CreateDirectory(@"TestOrders");
            }
        }

        public void CreateOrder(Order newOrder, DateTime date, bool writeHeader = false)
        {
            var orders = LoadOrders(date);
            orders.Add(newOrder);

            if (writeHeader)
            {
                StreamWriter writer = File.AppendText(FilePath);
                WriteHeader(writer);
            }

            WriteOrder(newOrder);
        }

        public void WriteHeader(StreamWriter writer)
        {
            using (writer)
            {
                writer.Write("OrderNumber,");
                writer.Write("CustomerName,");
                writer.Write("State,");
                writer.Write("TaxRate,");
                writer.Write("ProductType,");
                writer.Write("Area,");
                writer.Write("CostPerSquareFoot,");
                writer.Write("LaborCostPerSquareFoot,");
                writer.Write("MaterialCostTotal,");
                writer.Write("LaborCostTotal,");
                writer.Write("TaxTotal,");
                writer.Write("Total");
            }
        }

        //only call this after creating a new file
        public void WriteOrder(Order newOrder)
        {
            using (StreamWriter writer = File.AppendText(FilePath))
            {
                writer.Write(Environment.NewLine);
                writer.Write(newOrder.OrderNumber + ",");
                writer.Write(newOrder.LastName + ",");
                writer.Write(newOrder.StateInfo.StateAbbreviation + ",");
                writer.Write(newOrder.StateInfo.TaxRate + ",");
                writer.Write(newOrder.ProductInfo.ProductType + ",");
                writer.Write(newOrder.Area + ",");
                writer.Write(newOrder.ProductInfo.CostPerSquareFoot + ",");
                writer.Write(newOrder.ProductInfo.LaborCostPerSquareFoot + ",");
                writer.Write(newOrder.MaterialCostTotal + ",");
                writer.Write(newOrder.LaborCostTotal + ",");
                writer.Write(newOrder.TaxTotal + ",");
                writer.Write(newOrder.Total + ",");
            }
        }

        public void DeleteOrder(int orderNumber, DateTime date)
        {
            var orders = LoadOrders(date);

            var order1 = orders.First(o => o.OrderNumber == orderNumber);

            orders.Remove(order1);

            OverwriteFile(orders);
        }

        public int HighestOrderNumber(DateTime date)
        {
            List<Order> orders = LoadOrders(date);
            return orders.Select(a => a.OrderNumber).Max();
        }

        public Order LoadOrder(int orderNumber, DateTime date)
        {
            SetFilePath(date);
            List<Order> orders = LoadOrders(date);
            return orders.FirstOrDefault(o => o.OrderNumber == orderNumber);


        }

        public void UpdateOrder(Order updatedOrder, DateTime date)
        {
            var orders = LoadOrders(date);

            var order1 = orders.First(o => o.OrderNumber == updatedOrder.OrderNumber);

            order1.LastName = updatedOrder.LastName;
            order1.StateInfo.StateAbbreviation = updatedOrder.StateInfo.StateAbbreviation;
            order1.StateInfo.StateName = updatedOrder.StateInfo.StateName;
            order1.Area = updatedOrder.Area;
            order1.LaborCostTotal = updatedOrder.LaborCostTotal;
            order1.ProductInfo.LaborCostPerSquareFoot = updatedOrder.ProductInfo.LaborCostPerSquareFoot;
            order1.MaterialCostTotal = updatedOrder.MaterialCostTotal;
            order1.ProductInfo.CostPerSquareFoot = updatedOrder.ProductInfo.CostPerSquareFoot;
            order1.ProductInfo.ProductType = updatedOrder.ProductInfo.ProductType;
            order1.StateInfo.TaxRate = updatedOrder.StateInfo.TaxRate;
            order1.TaxTotal = updatedOrder.TaxTotal;
            order1.Total = updatedOrder.Total;

            OverwriteFile(orders);

        }

        public void DeleteFile()
        {
            File.Delete(FilePath);
        }

        public void OverwriteFile(List<Order> orders )
        {
            File.Delete(FilePath);

            using (StreamWriter writer = File.CreateText(FilePath))
            {
                WriteHeader(writer);

                foreach (var order in orders)
                {
                    WriteOrder(order);
                }
            }
        }

        public void SetFilePath(DateTime date)
        {

            string sMonth = date.Month.ToString().PadLeft(2, '0');
            string sDay = date.Day.ToString().PadLeft(2, '0');

            string fileName = "Orders_" + sMonth + sDay + date.Year + ".txt";

            FilePath = @"TestOrders\" + fileName;
        }

        public void CreateFile(DateTime date)
        {        
            SetFilePath(date);

            File.Create(FilePath).Dispose();

        }

        public List<Order> LoadOrders(DateTime date)
        {
            SetFilePath(date);

            List<Order> orders = new List<Order>();

            var reader = File.ReadAllLines(FilePath);

            for (int i = 1; i < reader.Length; i++)
            {
                var columns = reader[i].Split(',');

                var order = new Order();
                order.StateInfo = new State();
                order.ProductInfo = new Product();
                

                order.OrderNumber = Int32.Parse(columns[0]);
                order.LastName = columns[1];
                order.StateInfo.StateAbbreviation = columns[2];
                order.StateInfo.TaxRate = Decimal.Parse(columns[3]);
                order.ProductInfo.ProductType = columns[4];
                order.Area = Decimal.Parse(columns[5]);
                order.ProductInfo.CostPerSquareFoot = Decimal.Parse(columns[6]);
                order.ProductInfo.LaborCostPerSquareFoot = Decimal.Parse(columns[7]);
                order.MaterialCostTotal = Decimal.Parse(columns[8]);
                order.LaborCostTotal = Decimal.Parse(columns[9]);
                order.TaxTotal = Decimal.Parse(columns[10]);
                order.Total = Decimal.Parse(columns[11]);

                orders.Add(order);

            }

            return orders;
        }

        public bool FileExists(DateTime date)
        {
            SetFilePath(date);
            return File.Exists(FilePath);
        }

        public void ErrorLogger(string exception)
        {
            //if the file exists, just go ahead and write to it
            if (File.Exists(FilePathErrorLogger))
            {
                using (StreamWriter writer = File.AppendText(FilePathErrorLogger))
                {
                    writer.Write(Environment.NewLine);
                    writer.Write(DateTime.Now + " - ");
                    writer.Write(exception);
                }
            }

            //if the file doesn't exist, go ahead and create the file and log the first error
            else
            {
                File.Create(FilePathErrorLogger).Dispose();

                using (StreamWriter writer = File.AppendText(FilePathErrorLogger))
                {
                    writer.Write(Environment.NewLine);
                    writer.Write(DateTime.Now + " - ");
                    writer.Write(exception);
                }
            }

        }


    }
}