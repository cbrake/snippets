(defun make-cd (title artist rating ripped)
  (list :title title :artist artist :rating rating :ripped ripped))

(defvar *db* nil)

(defun save-db (filename)
  (with-open-file (out filename
		       :direction :output
		       :if-exists :supersede)
    (with-standard-io-syntax
      (print *db* out))))

(defun load-db (filename)
  (with-open-file (in filename)
    (with-standard-io-syntax
      (setf *db* (read in)))))

(defun add-record (cd) 
  (push cd *db*)
  (save-db "music.db"))

;(add-record (make-cd "Roses" "Kathy Mattea" 7 t))
;(add-record (make-cd "Fly" "Dixie Chicks" 8 t))
;(add-record (make-cd "Home" "Dixie Chicks" 9 t))

(defun dump-db ()
  (dolist (cd *db*)
    (format t "~{~a:~10t~a~%~}~%" cd)))

(defun prompt-read (prompt)
  (format *query-io* "~a: " prompt)
  (force-output *query-io*)
  (read-line *query-io*))

(defun prompt-for-cd ()
  (make-cd
   (prompt-read "Title")
   (prompt-read "Artist")
   (or (parse-integer (prompt-read "Rating") :junk-allowed t) 0)
   (y-or-n-p "Ripped [y/n]: ")))

(defun add-cds ()
  (if (not (y-or-n-p "Add CD? [y/n]: ")) (return))
  (loop (add-record (prompt-for-cd))
      (if (not (y-or-n-p "Another? [y/n]: ")) (return))))

; query functionality
(defun select (selector-fn)
  (remove-if-not selector-fn *db*))

(defun where(&key title artist rating (ripped nil ripped-p))
  #'(lambda (cd)
      (and
	(if title	(equal (getf cd :title) title) t)
	(if artist	(equal (getf cd :artist) artist) t)
	(if rating	(equal (getf cd :rating) rating) t)
	(if ripped-p	(equal (getf cd :ripped) ripped) t))))

(load-db "music.db")

(dump-db)

(add-cds)


