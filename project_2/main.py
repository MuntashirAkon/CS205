import numpy as np

def load_and_normalize_data(filename):
    """
    Load data from the filename and perform Z-sore normalization
    """
    # Load ASCII data into NumPy array
    data = np.loadtxt(filename)
    labels = data[:, 0]
    features = data[:, 1:]

    # Apply Z-score normalization
    mean = np.mean(features, axis=0)
    std = np.std(features, axis=0)
    # Handle zero-variance edge cases
    std[std == 0] = 1.0
    # Z-score = (x - mean) / std
    normalized_features = (features - mean) / std

    return labels, normalized_features

def distance_1nn(test_instance, training_set, current_features):
    """
    Calculate nearest neighbor using Eucledian distance.
    """
    # Keep only the active feature columns
    test_f = test_instance[current_features]
    train_f = training_set[:, current_features]

    # Euclidean Distance calculation
    distances = np.sqrt(np.sum((train_f - test_f) ** 2, axis=1))

    # Return the index of the closest match
    return np.argmin(distances)

def leave_one_out_cross_validation(labels, features, current_features):
    """
    Perform leave-one-out cross validation, and return the accuracy.
    """
    if not current_features:
        # No current features, just return 0.
        return 0.0

    correct_predictions = 0
    num_instances = features.shape[0]

    for i in range(num_instances):
        # Isolate the i-th row
        test_row = features[i, :]
        test_label = labels[i]

        # Leave out i-th row
        training_set = np.delete(features, i, axis=0)
        training_labels = np.delete(labels, i, axis=0)

        # Find distance
        best_match_idx = distance_1nn(test_row, training_set, current_features)

        # Retrieve the predicted label
        predicted_label = training_labels[best_match_idx]

        if predicted_label == test_label:
            # Count correct predictions
            correct_predictions += 1

    # Calculate accuracy: correct / total * 100
    return (correct_predictions / num_instances) * 100

def main():
    print("Welcome to Muntashir's Feature Selection Algorithm.")
    filename = input("Type in the name of the file to test: ")
    print("Type the number of the algorithm you want to run:\n1) Forward Selection\n2) Backward Elimination")
    choice = input()

    labels, features = load_and_normalize_data(filename)
    num_instances, num_features = features.shape
    print(f"\nThis dataset has {num_features} features with {num_instances} instances.\n")

    # Run a quick check with all features first to match assignment trace formatting
    all_features = list(range(num_features))
    baseline = leave_one_out_cross_validation(labels, features, all_features)
    print(f"Running nearest neighbor with all {num_features} features, using leaving-one-out evaluation, I get an accuracy of {baseline:.1f}%\n")

    print("Beginning search.")
    if choice == '1':
        # TODO: Implement forward selection function
        pass
    elif choice == '2':
        # TODO: Implement backward elimination function
        pass

if __name__ == "__main__":
    main()
