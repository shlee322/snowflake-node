var snowflake = require('../build/Release/SnowflakeNode');

var snow = new snowflake.snowflake;
snow.setEpoch("13E65B2781C");
snow.setMachine(30);
while(1)
{
    console.log(snow.generate());
}
