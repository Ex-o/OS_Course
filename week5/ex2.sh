touch input.txt
in="./input.txt"
while true
do
	if ln "$in" "$in.lock"
	then
		line="$(cat "$in" | tail -1)"
		nline=$((last_line+1))
		echo "$nline" >> "$in"
		rm "$in.lock"
	fi
done