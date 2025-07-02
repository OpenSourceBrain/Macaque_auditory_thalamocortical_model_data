import json
from pathlib import Path

def compare_json_files(file_path1, file_path2):
    """Compare two JSON files with neural network configuration data."""

    with open(file_path1, 'r') as f1, open(file_path2, 'r') as f2:
        data1 = json.load(f1)
        data2 = json.load(f2)
    
    if data1 == data2:
        print("JSON files are identical")
        return
    
    print("Differences found:")
    
    sections1 = set(data1.keys())
    sections2 = set(data2.keys())
    
    print(f"\nUnique sections in {file_path1}: {sections1 - sections2}")
    print(f"Unique sections in {file_path2}: {sections2 - sections1}")
    
    common_sections = sections1 & sections2
    for section in common_sections:
        if data1[section] != data2[section]:
            print(f"\nSection '{section}' differs:")
            compare_structures(data1[section], data2[section], section)

def compare_structures(struct1, struct2, path=""):
    """Compare two nested structures (dicts/lists) recursively."""
    if isinstance(struct1, dict) and isinstance(struct2, dict):
        keys1 = set(struct1.keys())
        keys2 = set(struct2.keys())
        
        for key in keys1 - keys2:
            print(f"  Key '{path}.{key}' only exists in first file")
        for key in keys2 - keys1:
            print(f"  Key '{path}.{key}' only exists in second file")
        
        for key in keys1 & keys2:
            compare_structures(struct1[key], struct2[key], f"{path}.{key}")
    
    elif isinstance(struct1, list) and isinstance(struct2, list):
        if len(struct1) != len(struct2):
            print(f"  List length differs at '{path}': {len(struct1)} vs {len(struct2)}")
        else:
            for i, (item1, item2) in enumerate(zip(struct1, struct2)):
                if item1 != item2:
                    print(f"  List item differs at '{path}[{i}]':")
                    print(f"    First:  {item1}")
                    print(f"    Second: {item2}")
    else:
        if struct1 != struct2:
            print(f"  Value differs at '{path}':")
            print(f"    First:  {struct1}")
            print(f"    Second: {struct2}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python compare_json.py <file1.json> <file2.json>")
        sys.exit(1)
    
    compare_json_files(sys.argv[1], sys.argv[2])