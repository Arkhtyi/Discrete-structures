/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

#include <utility>


animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker solid(fillColor);
    
        
    return fill(img, x, y, solid, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    
    gridColorPicker grid(gridColor, gridSpacing); 
     
    return fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    
    gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
     
    return fill(img, x, y, gradient, tolerance, frameFreq);
}


animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
     
     
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
     
    solidColorPicker solid(fillColor);
    
         
    return fill(img, x, y, solid, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**mp4.2
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker grid(gridColor, gridSpacing); 
     
    return fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
     gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
     
    return fill(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure. Then, until the structure is
     * empty, you do the following: 
     *
     * 1.     Remove a point from the ordering structure. 
     *
     *        If it has not been processed before and if its color is
     *        within the tolerance distance (up to and **including**
     *        tolerance away in square-RGB-space-distance) to the original
     *        point's pixel color [that is, \f$(currentRed - OriginalRed)^2 +
              (currentGreen - OriginalGreen)^2 + (currentBlue -
              OriginalBlue)^2 \leq tolerance\f$], then: 
     *        1.    indicate somehow that it has been processed (do not mark it
     *              "processed" anywhere else in your code) 
     *        2.    change its color in the image using the appropriate
     *              colorPicker
     *        3.    add all of its neighbors to the ordering structure, and 
     *        4.    if it is the appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq. 
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     */
    
    animation mainframe;
    
    
    
    int row = img.height();
    int col = img.width(); 
    
    int xcord = x;
    int ycord = y;
        
    int counter = 0;
    
    //Every fill algorithm requires an ordering structure
    OrderingStructure <int> tempx;
    OrderingStructure <int> tempy;
    
    //making arrays for checking if pixel is processed already
    bool ** processed = new bool* [col];
    for(int i = 0; i < col; i++){
    	processed[i] = new bool[row];
    	for(int j = 0; j < row; j++){
    		processed[i][j] = false;
    	}
    }
    
  
    // you simply place the given point in the ordering structure
    tempx.add(xcord);
    tempy.add(ycord);
    
    
    
    RGBAPixel origin = *img(x,y);
    
    
	//Then, until the structure is empty, you do the following
    while(tempx.isEmpty() == false && tempy.isEmpty() == false){
    	
       	//Remove a point from the ordering structure.
    	xcord = tempx.peek();
    	ycord = tempy.peek();
        	
        
		tempx.remove();
		tempy.remove();	
    	
    	
    	int redval = img(xcord,ycord)->red-origin.red;
    	int greenval = img(xcord,ycord)->green-origin.green;
    	int blueval = img(xcord,ycord)->blue-origin.blue;
    	
    	
    	//If it has not been processed before and if its color is within the tolerance distance
    	if(!processed[xcord][ycord] ){
    		//indicate somehow that it has been processedprocessed[xcord][ycord] = true
    		processed[xcord][ycord] = true;
     		if (redval*redval + greenval*greenval + blueval*blueval <= tolerance){
				//change its color in the image using the appropriate colorPicker
				*img(xcord,ycord) = fillColor(xcord,ycord);
				
				
				//add all of its neighbors to the ordering structure
				if(xcord+1 < row && ycord < col ) {
					tempx.add(xcord+1);
					tempy.add(ycord);
					}
				if(xcord < row  && ycord + 1 < col ) {
					tempx.add(xcord);
					tempy.add(ycord+1);
					}
				if(xcord-1 >= 0 && xcord-1 < row && ycord < col ) {
					tempx.add(xcord-1);
					tempy.add(ycord);
					}
				if(xcord < row && ycord-1 < col && ycord -1 >= 0 ) {
					tempx.add(xcord);
					tempy.add(ycord-1);
					}
				
			
			//if it is the appropriate frame, send the current PNG to the animation 
				counter++;
				if(counter % frameFreq == 0){
					counter = 0;
					mainframe.addFrame(img);
				} 
			}
			
		}
		
		
    }
       
   	for(int i = 0; i < col; i++){
    	delete [] processed[i];
    } 
    
    delete [] processed;
       
    return mainframe;

}

