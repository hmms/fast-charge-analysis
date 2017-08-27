import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

name_of_noqc_csv = "noQC2.csv"
name_of_wqc_csv = "wQC2.csv"

df_noQC = pd.DataFrame.from_csv(name_of_noqc_csv, sep=',', index_col=None,parse_dates=False)
df_wQC = pd.DataFrame.from_csv(name_of_wqc_csv, sep=',', index_col=None,parse_dates=False)

if __name__ == "__main__":
       print df_noQC
       t = np.arange(0.0, 4.0, 0.01)

       f, (ax1, ax2, ax3, ax4) = plt.subplots(4, 1, sharex='col')



       ax1.plot(df_noQC['Charge_in_mAh'],color='r',label="noQC")
       ax1.plot(df_wQC['Charge_in_mAh'],color='b',label="wQC2.0")
       ax1.set_xlim([0, 40000])
       ax1.legend(loc="upper right")
       ax1.set_title('Charge')
       ax1.set_ylabel('mAh')

       ax2.plot(df_noQC['Current'], color='r',label="noQC")
       ax2.plot(df_wQC['Current'], color='b',label="wQC2.0")
       ax2.set_xlim([0, 40000])
       ax2.legend(loc="upper right")
       ax2.set_title('Current')
       ax2.set_ylabel('A')

       ax3.plot(df_noQC['Voltage'], color='r',label="noQC")
       ax3.plot(df_wQC['Voltage'], color='b',label="wQC2.0")
       ax3.set_xlim([0, 40000])
       ax3.legend(loc="upper right")
       ax3.set_title('Voltage')
       ax3.set_ylabel('V')

       ax4.plot(df_noQC['Temperature'], color='r',label="noQC")
       ax4.plot(df_wQC['Temperature'], color='b',label="wQC2.0")
       ax4.set_xlim([0, 40000])
       ax4.legend(loc="upper right")
       ax4.set_title('Temperature')
       ax4.set_ylabel('$^\circ$C')

       plt.tight_layout()

       #Samsung Galaxy Note 4 - Charging from ~50% to Full, with and without Qualcomm QC 2.0
       #st = plt.suptitle("suptitle", fontsize="x-large")
       #st.set_y(0.95)

       #f.tight_layout()

       plt.show()