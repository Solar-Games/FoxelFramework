buildi: binary/ binary/glad.o binary/foxel_mathutil.o binary/foxel_renderer.o
	echo "Finished Building."

binary/:
	mkdir binary
binary/glad.o: foxel/glad.c includes/glad/glad.h
	gcc -fPIC -c -Os -Iincludes foxel/glad.c -o binary/glad.o
	echo "Built GLAD binary."
binary/foxel_mathutil.o: foxel/foxel_mathutil.c includes/foxel/foxel_mathutil.h
	gcc -fPIC -lm -c -Os -Iincludes foxel/foxel_mathutil.c -o binary/foxel_mathutil.o
	echo "Built the Math Utility binary."
binary/foxel_renderer.o: foxel/foxel_renderer.c includes/foxel/foxel_renderer.h
	gcc -fPIC -lm -c -Os -Iincludes foxel/foxel_renderer.c -o binary/foxel_renderer.o
	echo "Built the Rendering binary."
