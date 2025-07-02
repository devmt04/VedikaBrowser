## Issue 1: Cursor Still Visible When Search Bar Loses Focus

### Description

After calling `setCursorPosition()`, the cursor remains visible even when the `QLineEdit` is out of focus.

---

### Suspected Cause

* **Class**: `SearchBar`
* **Line**:

```cpp
urlInputBar->setCursorPosition(0);
```

### Status

Open
