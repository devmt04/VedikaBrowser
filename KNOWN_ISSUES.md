# Known Issues

This file tracks known bugs and stability issues for the project. Each issue includes steps to reproduce, suspected origin, and current status.

---

## Issue 1: Application Crash During Split View Transition

### Description

The application crashes when switching between Split and Single views under specific tab selection patterns.

---

### Steps to Reproduce

1. Open **more than 4 tabs**.
2. Switch to **Split View** and select **any 4 entries**.
3. Switch to **Single View**.
4. Switch back to **Split View**, this time selecting **only 2 entries**.
5. Switch to **Single View** again.
6. Attempt to switch to **Split View** once more.
7. **Application crashes.**

---

### Suspected Cause

- **Class**: `TabSelectionDialog`  
- **File**:  
  `lib/ui/WebAreaLayoutWidget/WebAreaLayoutManager/TabSelectionDialog/tabselectiondialog.cpp`  
- **Line**:

```cpp
QCheckBox *check = new QCheckBox(view->getTitle(), gridContainer);
```

### Additional Insights

- The crash occurs on any member function call to view (e.g., view->getTitle()).

### Status

Solved!
