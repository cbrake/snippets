
#let display(arr) = {
    // Initialize a variable to store the sum
    let total = 0
    
    // Iterate over each element in the array
    for num in arr {
        // Add the current element to the total sum
        //total += num
        [value: #num \
        ]
    }

    [all done]
}

// Example usage:
#display(([hi], [there]))
