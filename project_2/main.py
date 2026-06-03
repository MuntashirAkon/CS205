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

def distance_nn(test_instance, training_set, current_features):
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
        best_match_idx = distance_nn(test_row, training_set, current_features)

        # Retrieve the predicted label
        predicted_label = training_labels[best_match_idx]

        if predicted_label == test_label:
            # Count correct predictions
            correct_predictions += 1

    # Calculate accuracy: correct / total * 100
    return (correct_predictions / num_instances) * 100

def forward_selection(labels, features, considered_features):
    """
    The forward selection greedy search algorithm.
    """
    num_features = len(considered_features)
    current_features = []

    # Track the global best data
    global_best_features = []
    global_best_accuracy = 0.0

    # Loop through every level of the search tree
    for _ in considered_features:
        best_local_feature = None
        best_local_accuracy = -1.0

        # Try adding each feature that isn't already selected
        for feature_idx in considered_features:
            if feature_idx not in current_features:
                # Create a temporary subset
                candidate_set = current_features + [feature_idx]
                display_set = [f + 1 for f in candidate_set]

                # Evaluate the subset's accuracy
                accuracy = leave_one_out_cross_validation(labels, features, candidate_set)
                print(f"    Using feature(s) {{{','.join(map(str, display_set))}}} accuracy is {accuracy:.1f}%")

                # Track the best option at this level
                if accuracy > best_local_accuracy:
                    best_local_accuracy = accuracy
                    best_local_feature = feature_idx

        # Store the best local feature to the search path
        current_features.append(best_local_feature)
        print()

        # Update the global accuracy
        if best_local_accuracy > global_best_accuracy:
            global_best_accuracy = best_local_accuracy
            global_best_features = list(current_features)
        elif best_local_accuracy < global_best_accuracy:
            # Drops in accuracy!
            if len(current_features) != num_features:
                print("(Warning, Accuracy has decreased! Continuing search in case of local maxima)")

        if len(current_features) != num_features:
            display_current = [f + 1 for f in current_features]
            print(f"Feature set {{{','.join(map(str, display_current))}}} was best, accuracy is {best_local_accuracy:.1f}%\n")

    # Print final result
    display_global_best = [f + 1 for f in global_best_features]
    print(f"Finished search!! The best feature subset is {{{','.join(map(str, display_global_best))}}}, "
          f"which has an accuracy of {global_best_accuracy:.1f}%")

def backward_elimination(labels, features, considered_features):
    """
    The backward elimination greedy search algorithm.
    """
    # Start with all features active
    current_features = considered_features

    # Evaluate the baseline accuracy with the all features
    initial_accuracy = leave_one_out_cross_validation(labels, features, current_features)

    # Track the global best data
    global_best_features = list(current_features)
    global_best_accuracy = initial_accuracy

    # Systematically eliminate features until only 1 remains
    for _ in range(len(considered_features) - 1):
        worst_local_feature = None
        best_local_accuracy = -1.0

        # Try removing each feature from the active set
        for feature_idx in current_features:
            # Create a temporary subset by removing feature_idx
            candidate_set = [f for f in current_features if f != feature_idx]
            display_set = [f + 1 for f in candidate_set]

            # Evaluate the subset's accuracy
            accuracy = leave_one_out_cross_validation(labels, features, candidate_set)
            print(f"    Using feature(s) {{{','.join(map(str, display_set))}}} accuracy is {accuracy:.1f}%")

            # Track the worst option at this level
            if accuracy > best_local_accuracy:
                best_local_accuracy = accuracy
                worst_local_feature = feature_idx

        # Remove the worst local feature from the search path
        current_features.remove(worst_local_feature)
        print()

        # Update the global accuracy
        if best_local_accuracy > global_best_accuracy:
            global_best_accuracy = best_local_accuracy
            global_best_features = list(current_features)
        elif best_local_accuracy < global_best_accuracy:
            # Drops in accuracy!
            if len(current_features) > 1:
                print("(Warning, Accuracy has decreased! Continuing search in case of local maxima)")

        if len(current_features) > 1:
            display_current = [f + 1 for f in current_features]
            print(f"Feature set {{{','.join(map(str, display_current))}}} was best, accuracy is {best_local_accuracy:.1f}%\n")

    # Print final result
    display_global_best = [f + 1 for f in global_best_features]
    print(f"Finished search!! The best feature subset is {{{','.join(map(str, display_global_best))}}}, "
          f"which has an accuracy of {global_best_accuracy:.1f}%")

def main():
    print("Welcome to Muntashir's Feature Selection Algorithm.")
    filename = input("Type in the name of the file to test: ")
    print("Type the number of the algorithm you want to run:\n1) Forward Selection\n2) Backward Elimination")
    choice = input()

    labels, features = load_and_normalize_data(filename)
    num_instances, num_features = features.shape
    print(f"\nThis dataset has {num_features} features (not including the class attribute), with {num_instances} instances.\n")

    # Run a quick check with all features first to match assignment trace formatting
    all_features = list(range(num_features))
    # all_features = [1, 5, 6]
    baseline = leave_one_out_cross_validation(labels, features, all_features)
    print(f"Running nearest neighbor with all {num_features} features, using leaving-one-out evaluation, I get an accuracy of {baseline:.1f}%\n")

    print("Beginning search.\n")
    if choice == '1':
        forward_selection(labels, features, all_features)
    elif choice == '2':
        backward_elimination(labels, features, all_features)

if __name__ == "__main__":
    main()
