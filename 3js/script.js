var distance = 400;

function init() {
// Create an empty scene
var scene = new THREE.Scene();
// Create a basic perspective camera
var camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );
camera.position.set(100, -400, 2000);
scene.add(camera);
// Create a renderer with Antialiasing
var renderer = new THREE.WebGLRenderer({antialias:true});
// Configure renderer clear color
renderer.setClearColor("#000000");
// Configure renderer size
renderer.setSize( window.innerWidth, window.innerHeight );
// Append Renderer to DOM
document.body.appendChild( renderer.domElement );

createSpheres();
//createDiamond();
//createSpace();

renderer.render(scene, camera);
};

function createSpheres() {
	spheres = new THREE.Object3D();
	for (var i=0; i<80; i++) {
		var sphere = new THREE.SphereGeometry(4, Math.random() * 12, Math.random() * 12);
		var material = new THREE.MeshPhongMaterial({color: Math.random()* 0xff00000 - 0xff00000, shading: THREE.FlatShading,})

		var particle = new THREE.Mesh(sphere, material);
		particle.position.x = Math.random() * distance * 10;
		particle.position.y = Math.random() * -distance * 6;
		particle.position.z = Math.random() * distance * 4;
		particle.rotation.y = Math.random() * 2 * Math.PI;
		particle.scale. = particle.scale.y = particle.scale.z = Math.random() *12 +5;

		spheres.add(particle);
	}
	spheres.position.y = 500;
	spheres.position.x = -2000;
	spheres.position.z = -100;
	spheres.rotation.y = Math.PI * 600;

	scene.add(spheres);
}

// Create a Cube Mesh with basic material
/*var geometry = new THREE.BoxGeometry( 1, 1, 1 );
var material = new THREE.MeshBasicMaterial( { color: "#433F81" } );
var cube = new THREE.Mesh( geometry, material );

//Create a Cone Mesh
//var geometry = new THREE.ConeGeometry( 5, 20 32 );
//var material = new THREE.MeshBasicMaterial( { color : 0xffff00} );
//var cone = new THREE.Mesh( geometry, material );

// Add cube to Scene
scene.add( cube );
//scene.add( cone );

// Render Loop
var render = function () {
  requestAnimationFrame( render );

  cube.rotation.x += 0.01;
  cube.rotation.y += 0.01;
  cube.rotation.z += 0.01;

  // Render the scene
  renderer.render(scene, camera);
};

render();
*/

//https://medium.com/@PavelLaptev/three-js-for-beginers-32ce451aabda