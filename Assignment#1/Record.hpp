//
//  Record.hpp
//  Assignment#1
//
//  Created by Farooq Khan on 2/5/16.
//  Copyright © 2016 Farooq Khan. All rights reserved.
//

#ifndef Record_hpp
#define Record_hpp

#include <iostream>

enum RecordType{
    
    Order = 0, Payment = 1
};

class Record{
    
public:
    
    RecordType rec_Type;
    double paymentAmount;
    char itemName[20];
    int quantity;
    long int transactionNumber;
    
};

#endif /* Record_hpp */
