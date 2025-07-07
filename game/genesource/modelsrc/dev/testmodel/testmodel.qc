$modelname	"dev\testmodel.mdl"
$cdmaterials	"models\dev"

$staticprop
$surfaceprop	default
$contents	"solid"
$opaque

$body mesh	"testmesh.dmx"

$lod 21 {
	replacemodel "testmesh.dmx" "testmesh_lod1.dmx"
	nofacial
}

$lod 42 {
	replacemodel "testmesh.dmx" "testmesh_lod2.dmx"
	nofacial
}

$lod 64 {
	replacemodel "testmesh.dmx" "testmesh_lod3.dmx"
	nofacial
}

/*$lod 96 {
	replacemodel "testmesh.dmx" "testmesh_lod4.dmx"
	nofacial
}*/

$shadowlod
{
	replacemodel "testmesh.dmx" "testmesh_lod2.dmx"
	nofacial
}

$texturegroup skinfamilies
{
	{ "testmodel001"	"testmodel002"	"testmodel003"	"testmodel004"	"testmodel005" }
	{ "testmodel001a"	"testmodel002a"	"testmodel003"	"testmodel004"	"testmodel005a" }
	{ "testmodel001b"	"testmodel002"	"testmodel003b"	"testmodel004b"	"testmodel005" }
	{ "testmodel001c"	"testmodel002c"	"testmodel003c"	"testmodel004c"	"testmodel005c" }
	{ "testmodel001d"	"testmodel002d"	"testmodel003d"	"testmodel004d"	"testmodel005d" }
	{ "testmodel001e"	"testmodel002e"	"testmodel003e"	"testmodel004e"	"testmodel005e" }
}

$sequence ref	"testmesh.dmx" {
	fps 1
	fadein 0.2
	fadeout 0.2
	loop
}

$collisionmodel	"testmesh_lod3.dmx" {
	$mass 64
	$concave
}
