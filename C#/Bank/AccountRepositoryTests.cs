using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using SGBank.Data;
using SGBank.Models;
using SGBank.BLL;

namespace SGBank.Tests
{
    [TestFixture]
    public class AccountRepositoryTests
    {
        [Test]
        public void CanLoadAccount()
        {
            var repo = new AccountRepository();

            var account = repo.LoadAccount(1);

            Assert.AreEqual(1, account.AccountNumber);
            Assert.AreEqual("Mary", account.FirstName);
        }

        [Test]
        public void UpdateAccountSucceeds()
        {
            var repo = new AccountRepository();
            var accountToUpdate = repo.LoadAccount(1);
            accountToUpdate.Balance = 500.00M;
            repo.UpdateAccount(accountToUpdate);

            var result = repo.LoadAccount(1);

            Assert.AreEqual(500.00M, result.Balance);

        }

        [Test]
        public void AccountDepositSucceeds()
        {
            var repo = new AccountRepository();
            var accountToDeposit = repo.LoadAccount(1);
            var accountManager = new AccountManager();
            var response = accountManager.Deposit(accountToDeposit, 150M);

            Assert.AreEqual(497M, response.Data.NewBalance);
            Assert.AreEqual(150M, response.Data.DepositAmount);
            Assert.AreEqual(true, response.Success);

        }

        [Test]
        public void AccountDepositFailsZero()
        {
            var repo = new AccountRepository();
            var accountToDeposit = repo.LoadAccount(2);
            var accountManager = new AccountManager();
            var response = accountManager.Deposit(accountToDeposit, 0);

            Assert.IsFalse(response.Success);

        }

        [Test]
        public void AccountWithdrawSucceeds()
        {
            var repo = new AccountRepository();
            var accountToWithdraw = repo.LoadAccount(3);
            var accountManager = new AccountManager();
            var response = accountManager.Withdraw(accountToWithdraw, 100M);

            Assert.AreEqual(455M, response.Data.NewBalance);
            Assert.AreEqual(100M, response.Data.WithdrawAmount);
            Assert.AreEqual(true, response.Success);
        }

        [Test]
        public void AccountWithdrawFails()
        {
            var repo = new AccountRepository();
            var accountToWithdraw = repo.LoadAccount(2);
            var accountManager = new AccountManager();
            var response = accountManager.Withdraw(accountToWithdraw, 200M);

            Assert.AreEqual(false, response.Success);
        }

        //public int HighestAccountNumber()
        [Test]
        public void CheckHighestAccountNumber()
        {
            var repo = new AccountRepository();

            int result = repo.HighestAccountNumber();

            Assert.AreEqual(4, result);
        }

        [Test]
        public void CheckAddAccount()
        {
            var repo = new AccountRepository();
            var newAccount = new Account()
            {
                FirstName = "Homer",
                LastName = "Simpson",
                Balance = 500
            };


            repo.AddAccount(newAccount);
            repo.GetAllAccounts();
            var result = repo.LoadAccount(repo.HighestAccountNumber());

            Assert.AreEqual(result.Balance, newAccount.Balance);
            Assert.AreEqual(result.LastName, newAccount.LastName);
            Assert.AreEqual(result.FirstName, newAccount.FirstName);
            Assert.AreEqual(result.AccountNumber, 5);
        }

        [Test]
        public void DeleteSuccess()
        {
            var repo = new AccountRepository();
            
            repo.RemoveAccount(3);

            var account = repo.LoadAccount(3);

            Assert.IsNull(account);
        }

    }
}
