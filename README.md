# Delivery Shipment Assignment

## How to Run

1. Make sure the following files are in the same project folder:

   * `main.cpp`
   * `Data.txt`

2. Make sure `Data.txt` contains the delivery data in comma-separated format:

```text
ID,Area,Priority,Package Weight
1,Nasr City,2,4.5
2,Maadi,1,2.0
...
```

3. Compile the program using a C++ compiler

4. Run the program:

---

## 1. Explain Your Solution Approach

I first read all delivery requests from the input file and store them in a vector of `delivery` structures. Each delivery contains its ID, area, priority, package weight, and a `valid` flag.

I sort the main vector according to priority.

After sorting, I create a map where each area contains pointers to the deliveries belonging to that area. I use pointers so that changing the `valid` value through the map also changes the original delivery stored in the main vector.

I then go through the main vector in priority order. When I find a delivery that is still valid, I use its area to find the other deliveries from the same area that also has to be valid.

The first delivery starts a shipment. I then check the other deliveries from the same area and add a delivery if doing so keeps the total shipment weight at or below 10 kg. When a delivery is added to a shipment, its `valid` flag is changed to `false` so next time i go into the loop again i ignore it.

This continues until all deliveries have been assigned to a shipment.

The priority determines which delivery is considered first, while the area and 10 kg capacity determine which other deliveries can be grouped with it.

---

## 2. What Was the Most Difficult Part of the Assignment?

The most difficult part was deciding how to handle both priority and area grouping at the same time.

Sorting by priority alone first made me think about searching for areas afterward but then i thought of another approach which is the map of each area

Another challenge was keeping track of deliveries that had already been assigned. I used a `valid` Boolean for this instead of deleting deliveries from the vector and the map.

Using pointers in the area map was also important because the map needs to refer to the same delivery objects stored in the main vector rather than having to search for it each time in the vector.

---

## 3. Are There Situations Where Your Algorithm May Not Produce the Best Possible Grouping?

Yes.

The algorithm uses a greedy approach. It starts with the highest-priority unprocessed delivery and then adds compatible deliveries from the same area whenever they fit within the remaining capacity.

Because it makes these decisions one shipment at a time, it does not always find the combination that minimizes the total number of shipments.

In other situations, different combinations could produce a more efficient overall grouping.

However, the algorithm still respects the main requirements: priority is considered, deliveries are grouped by area where possible, the 10 kg capacity is never exceeded, and every delivery is assigned exactly once.

---

## 4. If the Input Contained 1,000,000 Delivery Requests, What Part of Your Solution Might Become Slow or Memory-Intensive?

The main vector and the area map would both need a lot more memory because they store information for every delivery.

The sorting operation would also become more expensive in time .

The  building process could also become slow depending on how many deliveries belong to the same area because it will contain more comparisons.

Therefore, both memory usage and processing time could become significant with 1,000,000 delivery requests.

---

## 5. What Would You Improve If You Had Another Day to Work on the Solution?

1. improve the grouping algorithm from greedy to more sufficient algorithm

2- add input validation for the data like negative weight or priority

3- create functions instead of putting everything in the main

4-testing using Larger data also contain invalid data to test edge cases or the main workflow

## 6. Additional Feature

I added a `valid` boolean to each delivery to keep track of whether it has already been processed and assigned to a shipment.

When a delivery is assigned to a shipment it's `valid` value becomes `false` allowing the algorithm to skip processed delivers

i chose this feature because it made it easier to track the state of each delivery without having to delete it from the map or the vector

## 7. Edge Cases

The program handles the required edge cases as follows:

1. **No deliveries**

   If the input file contains no delivery requests, the program will not process anything. It will simply run and terminate without producing any output or errors.

2. **A delivery heavier than 10 kg**

   There are two possible approaches for a delivery that exceeds the 10 kg vehicle capacity. The first approach is to divide it into smaller deliveries. For example, a 15 kg delivery could be divided into two 7.5 kg deliveries with the same priority and area.

   The second approach is to treat the delivery as indivisible and ignore it because it cannot fit into a single shipment. I chose the second approach for this solution. If a delivery weighs more than 10 kg, the program marks it as invalid and skips it so that it cannot be assigned to a shipment that would exceed the 10 kg limit.

3. **Multiple deliveries with the same priority**

   If multiple deliveries have the same priority, the program processes them according to their order in the sorted vector. Since priority is the main factor used for sorting, deliveries with the same priority do not have another rule to choose one over another

4. **Adding the next package would exceed the vehicle capacity**

   If adding the next delivery would make the shipment exceed 10 kg, the program does not add that delivery to the current shipment. It continues checking other deliveries from the same area to find one that can fit within the remaining capacity. If no suitable delivery can be added, the shipment contains only the deliveries that fit within the 10 kg limit.


