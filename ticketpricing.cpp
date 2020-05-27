//============================================================================
// Name        : algorithms.cpp
// Author      : Anton Kovalev
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <limits>
#include <deque>          // std::deque
//#include <queue>          // std::queue
#include <cstdio>
#include <stdio.h>
#include <string>

using namespace std;

using tuplePair = tuple<int,int>;

class costStartPair
{

public:

    costStartPair(int cost = 0, int start = 0)
    : m_costStart(make_tuple(cost, start) )
    {

    }

    void setStart(int n)
    {
        get<1>(m_costStart) = n;
    }

    int getStart()
    {
        return get<1>(m_costStart);
    }

    void setCost(int n)
    {
        get<0>(m_costStart) = n;
    }

    int getCost()
    {
        return get<0>(m_costStart);
    }

private:
    tuplePair m_costStart;

};

class priceSeatPair
{

public:

    priceSeatPair(int price = 0, int seats = 0)
    : m_priceSeat(make_tuple(price, seats) )
    {

    }

    void setSeats(int n)
    {
        get<1>(m_priceSeat) = n;
    }

    int getSeats()
    {
        return get<1>(m_priceSeat);
    }

    void setPrice(int n)
    {
        get<0>(m_priceSeat) = n;
    }

    int getPrice()
    {
        return get<0>(m_priceSeat);
    }

private:
    tuplePair m_priceSeat;

};

costStartPair maxElem(costStartPair& firstTuple, int firstCost,
                      costStartPair& secondTuple, int secondCost)
{

    if(firstCost > secondCost)
    {
        return costStartPair(firstCost, firstTuple.getStart());
    }
    else if(secondCost > firstCost)
    {
        return costStartPair(secondCost, secondTuple.getStart());
    }
    else
    {
       return costStartPair(secondCost, 
                        firstTuple.getStart() > secondTuple.getStart() ? secondTuple.getStart() : firstTuple.getStart() );
    }
}
costStartPair solve(vector<vector<costStartPair>>& dynamicTable,
                    vector<vector<priceSeatPair>>& priceTable, 
                    int weeks, 
                    int totalSeats)
{
costStartPair maxPrice = 0;
for(int j = 1; j <= weeks; ++j)
{
    for(int i = 0; i <= totalSeats; ++i)
    {
        if( dynamicTable[j-1][i].getCost() >= 0 )
        {
            for(int k = 0; k < priceTable[j].size(); ++k)
            {
                priceSeatPair p( priceTable[j][k] );
                if( p.getSeats() < i )
                {
                    dynamicTable[j][i - p.getSeats()] =
                        maxElem( dynamicTable[j][i - p.getSeats()], dynamicTable[j][i - p.getSeats()].getCost(), 
                             dynamicTable[j-1][i],                  p.getPrice() * p.getSeats() + dynamicTable[j-1][i].getCost() );
                }
                else if( p.getSeats() >= i ) // Sell all seats
                {
                    dynamicTable[j][0] =
                        maxElem( dynamicTable[j][0], dynamicTable[j][0].getCost(), 
                             dynamicTable[j-1][i],   p.getPrice() * i + dynamicTable[j-1][i].getCost() );
                    maxPrice = maxElem(maxPrice,                     maxPrice.getCost(),
                                       dynamicTable[j][0], dynamicTable[j][0].getCost());
                }
            }
        }
    }
}
    return maxPrice;
}

int main()
{

int n, w, k;
cin >> n >> w;
vector<vector<priceSeatPair>> priceTable(w+1);
for(int i = 0; i <= w; ++i)
{
    cin >> k;
    vector<priceSeatPair> week(k);
    for(int j = 0; j < k; ++j)
    {
        int price;
        cin >> price;
        week[j].setPrice(price);
    }
    for(int j = 0; j < k; ++j)
    {
        int nrSeats;
        cin >> nrSeats;
        week[j].setSeats(nrSeats);
    }
    priceTable[i] = week;
}

vector<vector<costStartPair>> dynamicTable( w+1, vector<costStartPair>(n+1,{-1,-1}) );

costStartPair ansWeekZero;
for(int i = 0; i < priceTable[0].size(); ++i)
{
    priceSeatPair p(priceTable[0][i]);
    if( p.getSeats() != 0 )
    {
        dynamicTable[0][ n-p.getSeats() ].setCost( p.getPrice() * p.getSeats() );
        dynamicTable[0][ n-p.getSeats() ].setStart( p.getPrice() );
        if(w == 0)
        {
            ansWeekZero = maxElem( ansWeekZero,                       ansWeekZero.getCost(),
                                   dynamicTable[0][ n-p.getSeats() ], p.getPrice()*p.getSeats() );
        }
    }
    else
    {
        dynamicTable[0][ n-p.getSeats() ].setCost( p.getPrice() * p.getSeats() );
        dynamicTable[0][ n-p.getSeats() ].setStart( p.getPrice() );
    }
    
}
if(w == 0)
{
    cout << ansWeekZero.getCost() <<endl;
    cout << ansWeekZero.getStart();
}
else
{
    costStartPair ans = solve(dynamicTable, priceTable, w, n);
    cout << ans.getCost() << endl;
    cout << ans.getStart();
}
return 0;
}