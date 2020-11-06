// size of the PCB - the +x are for printing margins
fth_length=68+2; 
fth_width=48+1;

// size of the 3D box
box_x = fth_length + 4;
box_y = fth_width + 4;
box_z = 6;


// it's a cube from which we remove 9 identical smaller cubes "noeuds"
// and one central cube.
difference() {
    cube([box_x, box_y, box_z], true);
    noeuds();
    central();
    usbAlim();
    touchSensor();
    roundedCorners();
}

// the PCB roughly has 9 cubes (3x3) which are joined together
module noeuds() {
    for (i = [-24:24:25 ]) {
        for (j = [-17: 17: 17] ) {
            translate([i, j, 1])  cube([18+3,12+3, box_z-1], true);
        }
    }
}

module central() {
    // cube central
    translate([0,0,1]) cube([45+4,30+4,box_z-1], true);   
}

// removes space for the USB power
module usbAlim() {
    color("red") translate([21, -20, 1]) cube([9.5,15, box_z-1], true);
}

// removes space to be able to access the touch sensor behind the PCB
module touchSensor() {
    color("blue") translate([-11, 3, -box_z]) linear_extrude(height=box_z+10) circle(r=7, $fn=30);
}

// just for a nicer look
module roundedCorners() {
    difference() {
        cube([box_x+5,box_y+5,box_z+10], true);
        
        for (i=[-26:52:32]) {
            for (j= [-16:32:25]) {
                translate([i, j,-1]) cylinder(h=box_z+20, r=13, $fn=300, center=true);
            }
        }
        cube([54+3, 52+3, box_z+20], center=true);
        cube([72+3, 32+3, box_z+20], center=true);

    }
}
