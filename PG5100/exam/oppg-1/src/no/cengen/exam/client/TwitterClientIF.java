package no.cengen.exam.client;

import no.cengen.exam.model.Tweet;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:02
 */
public interface TwitterClientIF extends Remote {
    void receiveTweet(Tweet tweet) throws RemoteException;
    ArrayList<String> getSubscriptions() throws RemoteException;
}
