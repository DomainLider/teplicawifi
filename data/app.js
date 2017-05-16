
var apprun=new Vue({
	el:"#apprun",
	data: {
		tInt:0,
		tExt:0,
		b1:0,
		b2:0,
	}
});

var datat=[
        { id:1, tInt:20, tExt:40, count:65},
        { id:2, tInt:15, tExt:43, count:75},
        { id:3, tInt:12, tExt:28, count:85},
        { id:4, tInt:25, tExt:90, count:95},
        { id:5, tInt:17, tExt:50, count:105},
	{ id:6, tInt:67, tExt:10, count:115}
    ]


function updateTemp(){
var a = new XMLHttpRequest();
a.open("GET","/status",true);
a.onreadystatechange = function() {
  if( this.readyState == 4) {
    if( this.status == 200) {
	console.log(this.responseText);
	let kkk=this.responseText;
	let b=JSON.parse(kkk);
	apprun.tInt=b.tInt;
	apprun.tExt=b.tExt;
	apprun.b1=b.b1;
	apprun.b2=b.b2;
	datat.push({id:b.count,tInt:b.tInt,tExt:b.tExt,b1:b.b1,b2:b.b2,count:b.count});
    }
    else console.log("HTTP error "+this.status+" "+this.statusText);
  }
}
a.send();
}

//setInterval(updateTemp,4000);


setInterval(function(){
	updateTemp();
	chartTemp.clearAll();
	chartTemp.parse(datat);
},4000);

var chartTemp=webix.ui({
            view:"chart",
            container:"chartTemp",
            type:"spline",
            height:500,
            with:500,

            xAxis:{
                template:"#count#"
            },
            yAxis:{
                start:0,
                step:10,
		end:100
                // end: 100
            },
            legend:{
                values:[
			{text:"tInt",color:"#1293f8"},
			{text:"tExt",color:"#66cc00"},
			{text:"b1",color:"#66aa00"},
			{text:"b2",color:"#aacc00"},		
			],
                align:"right",
                valign:"middle",
                layout:"y",
                width: 100,
                margin: 8
            },
            series:[
                {
                    value:"#tInt#",
                    item:{
                        borderColor: "#1293f8",
                        color: "#ffffff"
                    },
                    line:{
                        color:"#1293f8",
                        width:3
                    },
                    tooltip:{
                        template:"#tInt#"
                    }
                },
                {
                    value:"#tExt#",
                    item:{
                        borderColor: "#66cc00",
                        color: "#ffffff"
                    },
                    line:{
                        color:"#66cc00",
                        width:3
                    },
                    tooltip:{
                        template:"#tExt#"
                    }
                },
                {
                    value:"#b1#",
                    item:{
                        borderColor: "#66aa00",
                        color: "#ffffff"
                    },
                    line:{
                        color:"#66aa00",
                        width:3
                    },
                    tooltip:{
                        template:"#b1#"
                    }
                },
                {
                    value:"#b2#",
                    item:{
                        borderColor: "#aacc00",
                        color: "#ffffff"
                    },
                    line:{
                        color:"#aacc00",
                        width:3
                    },
                    tooltip:{
                        template:"#b2#"
                    }
                }
            ],
            data:  datat
        });
