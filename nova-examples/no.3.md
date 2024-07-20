#Complete NovaLang Code with Hypothetical Data and Smart Contract Logic:

// --- Functions for Analyzing Transactions ---

// Function to analyze a transaction
function analyze_transaction(txHash: string) -> string {
  // Fetch the transaction data
  let transaction = get_transaction_data(txHash);
  
  // Check if the transaction is a whale transaction
  if (is_whale(transaction.amount) && is_recent(transaction.timestamp)) {
    return "Potential whale transaction detected!";
  } else {
    return "Transaction is not a potential whale transaction.";
  }
}

// Function to determine if the transaction amount qualifies as a whale transaction
function is_whale(amount: int) -> bool {
  // For this example, we define a whale transaction as over 100,000 SOL
  return amount > 100000;
}

// Function to determine if the transaction happened recently (within the last hour)
function is_recent(timestamp: int) -> bool {
  // Define the current time
  let current_time = Date.now();
  
  // Check if the transaction happened within the last hour (3600000 milliseconds)
  return (current_time - timestamp) < 3600000;
}

// Function to get hypothetical transaction data
function get_transaction_data(txHash: string) -> Map {
  // This is a placeholder for actual API calls
  if (txHash == "TX_1234") {
    return {
      "amount": 500000, // 500,000 SOL 
      "sender": "SOLANA_WALLET_1",
      "receiver": "SOLANA_WALLET_2",
      "timestamp": Date.now() - 1800000 // 30 minutes ago
    };
  } else if (txHash == "TX_5678") {
    return {
      "amount": 1000, // Small transaction
      "sender": "SOLANA_WALLET_3",
      "receiver": "SOLANA_WALLET_4",
      "timestamp": Date.now() 
    };
  } else {
    // Default transaction for other hashes
    return {
      "amount": 250000, // 250,000 SOL
      "sender": "SOLANA_WALLET_5",
      "receiver": "SOLANA_WALLET_6",
      "timestamp": Date.now() - 1000000 // 16.67 minutes ago
    };
  }
}

// --- Smart Contract Logic ---

contract WhaleWatcher {
    // State variables
    let lastWhaleDetected: int = 0; 
    let whaleTransactions: List<Map> = [];

    // Function to analyze a transaction and update contract state
    function analyzeAndRecord(txHash: string) {
        let analysisResult = analyze_transaction(txHash);
        if (analysisResult == "Potential whale transaction detected!") {
            let txData = get_transaction_data(txHash);
            whaleTransactions.push(txData);
            lastWhaleDetected = Date.now(); // Record the last detection time
        }
    }

    // Function to check if a whale transaction has been detected recently
    function hasRecentWhale() -> bool {
        let now = Date.now(); 
        return (now - lastWhaleDetected) < 3600000; // Check if within the last hour 
    }

    // Function to get a list of recent whale transactions
    function getWhaleTransactions() -> List<Map> {
        return whaleTransactions; 
    }
}

// Main function to run the analysis and deploy the contract
function main() {
    // Deploy the WhaleWatcher contract
    let whaleWatcherContract = contracts.deploy_contract(wallet, WhaleWatcher.code);
    print("WhaleWatcher contract deployed at:", whaleWatcherContract.address);

    // Analyze a transaction
    whaleWatcherContract.call("analyzeAndRecord", "TX_1234");

    // Check if there has been a recent whale transaction
    let hasWhale = whaleWatcherContract.call("hasRecentWhale");

    if (hasWhale) {
        print("A whale transaction has been detected recently.");

        // Get recent whale transactions
        let whaleTxList = whaleWatcherContract.call("getWhaleTransactions");

        print("Recent whale transactions:", whaleTxList);
    } else {
        print("No recent whale transactions detected.");
    }

    // Analyze another transaction
    whaleWatcherContract.call("analyzeAndRecord", "TX_5678");

    // Check again if there has been a recent whale transaction
    hasWhale = whaleWatcherContract.call("hasRecentWhale");

    if (hasWhale) {
        print("A whale transaction has been detected recently.");

        // Get recent whale transactions
        whaleTxList = whaleWatcherContract.call("getWhaleTransactions");

        print("Recent whale transactions:", whaleTxList);
    } else {
        print("No recent whale transactions detected.");
    }

    // Test with additional hypothetical transactions
    whaleWatcherContract.call("analyzeAndRecord", "TX_91011");

    // Check if there has been a recent whale transaction
    hasWhale = whaleWatcherContract.call("hasRecentWhale");

    if (hasWhale) {
        print("A whale transaction has been detected recently.");

        // Get recent whale transactions
        whaleTxList = whaleWatcherContract.call("getWhaleTransactions");

        print("Recent whale transactions:", whaleTxList);
    } else {
        print("No recent whale transactions detected.");
    }
}

// Run the main function
main();
Explanation
WhaleWatcher Contract:
State Variables:

lastWhaleDetected: Stores the timestamp of the last whale transaction detected.
whaleTransactions: A list to store the details of recent whale transactions.
analyzeAndRecord Function:

Performs the same analysis as before.
If a whale transaction is detected:
Stores the transaction details in the whaleTransactions list.
Updates the lastWhaleDetected timestamp.
hasRecentWhale Function:

Checks if a whale transaction has been detected within the last hour.
getWhaleTransactions Function:

Returns the list of recent whale transactions. Using the Smart Contract: 

Deploy the WhaleWatcher contract.

Analyze transactions (TX_1234, TX_5678, and TX_91011).

Check if there has been a recent whale transaction.

Print the list of recent whale transactions if a whale transaction has been detected.

Running the Code:

Compile and run the script using the NovaLang compiler:
