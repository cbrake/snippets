#let sum(arr) = {
    // Initialize a variable to store the sum
    let total = 0
    
    // Iterate over each element in the array
    for num in arr {
        // Add the current element to the total sum
        //total += num
        [number #num]
    }
    
    // Return the total sum
    [total: #total]
}

// Example usage:
#sum((1, 2, 3, 4, 5))
