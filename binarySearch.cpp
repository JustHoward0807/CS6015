#include "catch.h"

//buggy code
int binarySearch(int arr[], int low, int high, int x)
{
    if (high > low)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, low, mid - 1, x);

        return binarySearch(arr, mid + 1, high, x);
    }
    return -1;
}


TEST_CASE( "Search Element in Array") {
    int a[8] = {4, 9, 21, 33, 35, 50, 55, 60};

    SECTION("Element_anywhere_middle_array"){
        REQUIRE( binarySearch (a,0,7,35) == 4 );
        REQUIRE( binarySearch (a,0,7,33) == 3 );
    }
    
    SECTION("edge_cases"){
        REQUIRE( binarySearch (a,0,7,4) == 0 );
        REQUIRE( binarySearch (a,0,7,60) == 7 );
        
    }
    
    SECTION("Element_not_in_array"){
        REQUIRE( binarySearch (a,0,7,3) == -1 );
        REQUIRE( binarySearch (a,0,7,30) == -1 );
    }
}
