// FAROOQ KHAN
// CISC 3130 - Data Structures
//
//  main.cpp
//  Assignment#1
//
//  Created by Farooq Khan on 2/4/16.
//  Copyright © 2016 Farooq Khan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "Customer.hpp"
#include "Record.hpp"

using namespace std;

void printCustomerInformation(Customer, ofstream &);


int main()
{
    
    ifstream masterRecordFile;          //  Customers' Information
    ifstream transactionRecordFile;     //  Paper trail of all trasactions
    ofstream newMasterFile;             //  New Master File with updated information
    ofstream outputFile;                //  File for Output.
    
    //
    // Open all the files
    //
    
    masterRecordFile.open("masterAccountsData");
    transactionRecordFile.open("transcationRecord");
    newMasterFile.open("newMaster");
    outputFile.open("output");
    
    if(!transactionRecordFile.good()){
        outputFile << "transaction Record file not found" << endl;
    }
    
    if (!masterRecordFile.good()) {
        outputFile << "Master Account File not found..." << endl;
    }
    
    Customer tempCustomer;
    vector<Customer> customer;
    
    Record record;
    char transactionType;
    double SumOfPayments;
    
    bool duplicateCustomer = false;
    
    
    // New Master File Header
    newMasterFile << "-------------------------------------------" << endl;
    newMasterFile << "************| New Master File |************" << endl;
    newMasterFile << "-------------------------------------------" << endl << endl;
    
    // Output File Header
    outputFile << "-------------------------------------------------" << endl;
    outputFile << "*****************| Output File |*****************" << endl;
    outputFile << "-------------------------------------------------" << endl << endl;
    
    while (true) {
        
        masterRecordFile >> tempCustomer.customer_Number;
        masterRecordFile >> tempCustomer.name;
        masterRecordFile >> tempCustomer.balanceDue;
        
        printCustomerInformation(tempCustomer, outputFile);
        
        for (int i = 1; i < customer.size(); i++) {
            
            if(customer.size() == 0){
                
                //
                // Do nothing - Dont want null pointer exception.
                //
                
            } else if(customer[i-1].customer_Number == tempCustomer.customer_Number){
                
                duplicateCustomer = true;
                
                outputFile << "Error: Duplicate customer record found..." << endl;
            }
        }
        while (duplicateCustomer == false) {
            
            int customerNumberPerTransaction = NULL;
            
            transactionRecordFile >> transactionType;
            
            if (transactionType == 'P'){
                
                record.rec_Type = Payment;
            }
            else if (transactionType == 'O') {
                
                record.rec_Type = Order;
            }
            
            transactionRecordFile >> record.transactionNumber;
            transactionRecordFile >> customerNumberPerTransaction;
            
            if (record.rec_Type == Payment ) {
                
                transactionRecordFile >> record.paymentAmount;
                
                // Checking for transaction that doesn't relate with any of the provided customers
                
                
            }else if(record.rec_Type == Order){
                
                transactionRecordFile >> record.itemName;
                transactionRecordFile >> record.quantity;
                transactionRecordFile >> record.paymentAmount;
            }
            
            if (customerNumberPerTransaction == tempCustomer.customer_Number)
            {
                if (record.rec_Type == Payment) {
                    tempCustomer.balanceDue -= record.paymentAmount;
                    outputFile << record.transactionNumber;
                    outputFile <<  "\t\tPayment: $" << record.paymentAmount << endl;
                }
                else if(record.rec_Type == Order) {
                    tempCustomer.balanceDue += (record.paymentAmount*record.quantity);
                    outputFile << record.transactionNumber;
                    outputFile <<"\t" <<  record.itemName << " x " << record.quantity << "  @ $" << record.paymentAmount*record.quantity << endl;
                }
            }
            
            //
            // Reached end of the file? If so, Then stop reading it.
            //
            if(transactionRecordFile.eof()) break;
            
        }
        
        if (duplicateCustomer != true) {
            
            //
            //  Adding new customer.
            //
            
            customer.push_back(tempCustomer);
            
            outputFile << "\n\t\t\tBalance Due: $" << (tempCustomer.balanceDue-SumOfPayments) << endl << endl;
        }
        
       
        
        //
        // Clear file streams for next customer.
        //
        
        transactionRecordFile.clear();
        transactionRecordFile.seekg(0);
        
        if (duplicateCustomer) {
            newMasterFile << tempCustomer.customer_Number;
            newMasterFile << "\t\t" << tempCustomer.name;
            newMasterFile << "\t\t" << "Duplicate Customer"<< endl;
        } else
        {
            newMasterFile << tempCustomer.customer_Number;
            newMasterFile << "\t\t" << tempCustomer.name;
            newMasterFile << "\t\t" << tempCustomer.balanceDue<< endl;
        }
        
        
        
        //
        // DuplicateCustomer is switched back to false to continue reading the rest of data.
        //
        
        duplicateCustomer = false;
        
        if (masterRecordFile.eof()) {
            break;
        }
        
    }
    
    //
    // Close all the files
    //
    
    transactionRecordFile.close();
    masterRecordFile.close();
    newMasterFile.close();
    outputFile.close();
    return 0;
}

void printCustomerInformation(Customer customer, ofstream &outputFile){
    outputFile << "-----------------------------------------------" << endl;
    outputFile << "Name: " << customer.name << "\t\t\t" << "#" << customer.customer_Number << endl;
    outputFile << "-----------------------------------------------" << endl;
    outputFile << "\n\t\t\t" << "Previous Balance: $";
    outputFile << setprecision(2) << fixed << customer.balanceDue << endl << endl;
}
