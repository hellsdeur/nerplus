import sys
from pathlib import PurePath
import pandas as pd


def main():
    csv_path: PurePath = PurePath(sys.argv[1])

    df = pd.read_csv(csv_path, sep=',')

    df.to_csv(PurePath(csv_path.parent, csv_path.stem + ".tsv"), sep='|', index=False)

if __name__ == "__main__":
    main()
