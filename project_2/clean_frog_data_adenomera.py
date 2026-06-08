import pandas as pd
import numpy as np
from scipy import stats

def clean_frog_data_species(input_file, output_file):
    print("Loading raw dataset...")
    df = pd.read_csv(input_file)
    
    # Define the two species
    class_1 = 'AdenomeraHylaedactylus'
    class_2 = 'AdenomeraAndre'
    
    # Separate the two classes
    print(f"Filtering dataset to only include {class_1} and {class_2}...")
    df_c1 = df[df['Species'] == class_1]
    df_c2 = df[df['Species'] == class_2]
    
    # Downsample class 1 to balance the dataset
    # 1000 (Class 1) + 672 (Class 2) = 1,672 total instances
    df_c1_sampled = df_c1.sample(n=1000, random_state=42)
    
    # Combine the balanced data back together
    df_filtered = pd.concat([df_c1_sampled, df_c2])
    
    # Create a new numerical class column (1 and 2)
    df_filtered['Target_Class'] = df_filtered['Species'].map({class_1: 1, class_2: 2})
    
    # Isolate the feature columns
    feature_cols = [col for col in df.columns if 'MFCC' in col]

    # Calculate absolute Z-scores for all the continuous features
    print(f"Instances before outlier removal: {len(df_filtered)}")
    z_scores = np.abs(stats.zscore(df_filtered[feature_cols]))
    
    # Keep only the rows where all 22 features have a Z-score less than 3
    df_cleaned = df_filtered[(z_scores < 3).all(axis=1)]
    
    removed_count = len(df_filtered) - len(df_cleaned)
    print(f"Removed {removed_count} outlier frogs based on Z-score value > 3.")
    
    # Rearrange columns to have class label first, then the 22 features
    final_columns = ['Target_Class'] + feature_cols
    df_final = df_cleaned[final_columns]
    
    # Shuffle the dataset
    df_final = df_final.sample(frac=1, random_state=42)
    
    # Export to a space-separated text file
    print(f"Exporting {len(df_final)} instances to {output_file}...")
    df_final.to_csv(output_file, sep=' ', header=False, index=False)
    
    print("Done!")

if __name__ == "__main__":
    clean_frog_data_species('Frogs_MFCCs.csv', 'frog_data_species_binary.txt')