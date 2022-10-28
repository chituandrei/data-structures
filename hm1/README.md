File organization:
	list.h includes double-linked-lists with all functions implemented (add_at,freeList,deleteNode etc..)
	statistici.h includes task 2.1
	filtrare.h includes task 2.2
	uniformizare.h includes task 2.3
	completare.h includes task 2.4
	st_delta.h includes task 2.5

Task 2.1
The average function calculates the arithmetic mean, the dev function calculates the deviation according to the given formula returning sum.
In the statistics function, I chose to go through the list from the 3rd element to len - 2 to be able to calculate the sum of 5 consecutive elements. 
For position i I need i+1,i+2,i-1,i-2 and this iteration will not generate a Seq Fault.

Task 2.2 
For the solution, I chose to use an auxiliary list called clist, which is sorted and selects the element from its middle.
At the end, I delete the last 4 nodes because after performing the function there will always be 4 values ​​less. 
Thus, I keep from 0 to n-5 the values ​​from the median filtering, and the values ​​n-4,n-3,n-2,n-1 are deleted.

Task 2.3 
The solving algorithm goes through the elements of the list changing the values ​​in the list according to the formula.

Task 2.4
Since w depends on i and k, the w values ​​will remain constant regardless of the data input type, so the w function calculates the numbers we need from the presented formulas.
In order not to retain in another auxiliary list, the neighbors are retained in left1,left2,left3,right1,right2,right3. 
Function C calculates the related values ​​depending on the timestamp we are at. 
At the end, I only do the iteration to complete the list in case the condition in the request is verified.

Task 2.5
After extracting the argument, I insert it as a parameter in the function. 
I keep the minimum and maximum to know where the intervals start and where they end, I sort the list, and then by iterating I display the elements.
