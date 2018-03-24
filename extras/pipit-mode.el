;;;;;;;;;; emacs pipit-mode for Pipit keymaps ;;;;;;;;;

(defvar pipit-font-lock-defaults
  `((("\\*" . font-lock-constant-face)
     ("\\." . font-lock-builtin-face)
     )))

(define-derived-mode pipit-mode fundamental-mode "pipit"
  "pipit mode is a major mode for editing Pipit keymap files"
  (setq font-lock-defaults pipit-font-lock-defaults)
  ;;make comments work
  (setq comment-start "#")
  (setq comment-end "")
  (modify-syntax-entry ?# "< b" pipit-mode-syntax-table)
  (modify-syntax-entry ?\n "> b" pipit-mode-syntax-table)
  ;;periods are parts of words
  (modify-syntax-entry ?. "w" pipit-mode-syntax-table)
  ;;asterisks are not, we can jump to them with forward-word
  (modify-syntax-entry ?* "." pipit-mode-syntax-table)
  ;;quotes are parts of words, to prevent string highlighting
  (modify-syntax-entry ?\" "w" pipit-mode-syntax-table)
  ;;A gnu-correct program will have some sort of hook call here.
  )

(provide 'pipit-mode)
(add-to-list 'auto-mode-alist '("\\.kmap\\'" . pipit-mode))
