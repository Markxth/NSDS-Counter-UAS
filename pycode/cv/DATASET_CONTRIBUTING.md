# Dataset Contribution Guidelines: Counter-UAS CV Team

Thanks for helping build the drone detection dataset. Following these guidelines lets us add your data without reformatting it by hand. 

# Please review the submission process (item 6) before sending any file.

---

## 1. Labeling Format

Pre-label your data in **YOLO format** by having **one `.txt` label file per image**, with the **same filename** as its image.

Each line in a label file is one bounding box:

```
0 x_center y_center width height
```

- Separate values with **spaces only.**
- Coordinates are **normalized** (0–1) relative to the image's width and height.
- If an image has no drones (a negative sample), include an **empty `.txt` file** for it.

**Example** (`purduepete0123_001.txt`):

```
0 0.512 0.338 0.041 0.027
0 0.774 0.602 0.019 0.015
```

## 2. Classes

The current dataset config supports **one class only** (pending modification, please consult this document whenever you want to contribute a dataset):

| ID | Class |
|----|-------|
| 0  | drone |

**Do not add new classes.** If you think we need another class, contact **me and Mark** first so we can decide whether to add it.

## 3. Image Requirements

- **Do not resize or pad images.** Submit them at their original resolution.
- Common formats (`.jpg`, `.png`) are fine. If it is an uncommon format, please message the CV team lead on discord or systems officer if CV team lead does not respond.

## 4. File Naming

Start every filename with an **identifier unique to you**, such as your Purdue username:
**ID of image should be numbered sequentially.**

```
<username>_<identifier_of_image>.jpg 
<username>_<identifier_of_image>.txt
```

Example: `purduepete0123_001.jpg` ↔ `purduepete0123_001.txt`

## 5. Folder Structure

Submit **only** an `images/` folder and a `labels/` folder, side by side:

```
<username>_batch_001/
├── images/
│   ├── purduepete0123_001.jpg
│   └── purduepete0123_002.jpg
└── labels/
    ├── purduepete0123_001.txt
    └── purduepete0123_002.txt
```

**DO NOT** split your data into train/val/test sets.

## 6. Submission Process

1. **Send a sample first.** Send about **20 image–label pairs**.
2. **Wait for approval.** We will either approve or reject the submission, with brief reasoning on the decision.
3. **Submit the full batch.** Once approved, send it as a zip named:

   ```
   <username>_batch_001.zip
   ```

   Number later batches in order (`_batch_002`, `_batch_003`, …).

An automated intake pipeline is WIP.

## 7. Current Data Needs

- **Real-world footage**, captured from video or collected as image sets
- **Tiny or distant drones**
- **Negatives** (no drone present): birds, planes, kites
- **Hard backgrounds**: drones against treelines, urban skies, and other cluttered environments

## 8. Auditing Existing Datasets

If you'd like to help audit our existing data, **DM the CV team lead or systems officer**. We currently have one dataset of about 75k images and are adding more quickly.
