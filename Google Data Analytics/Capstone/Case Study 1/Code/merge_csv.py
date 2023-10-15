import pandas as pd  # merge csv
from sys import argv  # read args from cli

print(f"Merging {len(argv)-1} files {str(argv[1:])}.")
# merge all args 1 to n-1
df_merged = pd.concat([pd.read_csv(f) for f in argv[1:-1]], ignore_index=True)
# store merged in nth arg

df_merged.to_csv(argv[-1], encoding="utf-8", index=False)
